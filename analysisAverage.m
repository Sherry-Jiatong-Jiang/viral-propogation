%===================================================================================================================================
%This code should only be used for data that has all reached fixation,
%i.e.data of completed jobs or after contatenation of data of timeout jobs. 

%Inputs: 1. Ne2start (Ne2 is fitted to data from this step to the end); 
%2. Ne1end (Ne1 is fitted to data from beginning to this step); 
%Both Ne2start and Ne1end are counted by simulation step beginning from
%labelling event (consistent with the graph axis). 
%The values can be estimated from the graph after initial trial run.
%should be set as integer times of v_steps.
%3. v_steps (visualizaiton_steps); 4. deme_strt; 5. deme_end (between
%deme_strt and deme_end, the average level of the last generated graph of phage 
%front profile is taken as the reference level for width calculation.
%The values can be estimated from the graph after initial trial run to make sure
%both points are in the plateau region); 6. demes (total deme number, =X, default is 100);
%7. seeds (random of random seeds, number of simulations taken
%for average. default is 20.)
 
%Output: -2/pH1(1) (early stage effective population size Ne1);
%-2/pH2(1) (late stage effective population size Ne2); fixsteps (fixation step); 
%SD1 (standard deviation of fixsteps); pF(1) (velocity); width (width); 
%SD2 (standard deviation of width).


%Speficy inputs before running

Ne2start=2000;
Ne1end=1000;
v_steps=20;
deme_strt=1;
deme_end=50;
demes=100;
seeds=20;


%===============================================================================================================================
%load data

sim0P_=cell(seeds,1);
sim0H_=cell(seeds,1);
sim0F2_=cell(seeds,1);
sim0L_=cell(seeds,1);

for j=1:1:seeds
    sim0P_{j}=load(sprintf('sim0P_%d.dat', j));
    sim0H_{j}=load(sprintf('sim0H_%d.dat', j));
    sim0F2_{j}=load(sprintf('sim0F2_%d.dat', j));
    %sim0L_{j}=load(sprintf('sim0L_%d.dat', j));
end


%Keep this as 1
half_vel=1;


%=================================================================
%Average sim0H

%finding the lengths of sim0H's
n2_=zeros(1,seeds);
p2_=zeros(1,seeds);
for j=1:1:seeds
    [n2_(j), p2_(j)] = size(sim0H_{j});
end

%finding the maximum length of sim0H's
p2 = max(p2_);


%append zero pads to tails so that all sim0H's are of the same length
new0H_=zeros(seeds,p2);
for j=1:1:seeds
    if p2>p2_(j)
        new0H_(j,:)=[sim0H_{j},zeros(1,p2-p2_(j))];
    else
        new0H_(j,:)=sim0H_{j};
    end
end


%leaving out the fixation 0s at the end
p2=p2-1;


t2 = linspace(0,v_steps*(p2-1),p2);


%calculate average sim0H
sim0H_ave = new0H_(1,:);
for j=1:1:seeds-1
    sim0H_ave = sim0H_ave + new0H_(j+1,:);
end
sim0H_ave = sim0H_ave/seeds;


%==================================================================
%Average sim0F2

%finding the lengths of sim0F2's
n5_=zeros(1,seeds);
p5_=zeros(1,seeds);
for j=1:1:seeds
    [n5_(j), p5_(j)] = size(sim0F2_{j});
end

%finding the minimum length of sim0F2's
p5 = min(p5_);

t5 = linspace(0,v_steps*(p5-1),p5);

%calculate average sim0F2
sim0F2_ave = sim0F2_{1}(1:p5);
for j=1:1:seeds-1
    sim0F2_ave = sim0F2_ave + sim0F2_{j+1}(1:p5);
end
sim0F2_ave = sim0F2_ave/seeds;


%==================================================================
%Average sim0P

%finding the lengths of sim0P's
n1_=zeros(1,seeds);
p1_=zeros(1,seeds);
for j=1:1:seeds
    [n1_(j), p1_(j)] = size(sim0P_{j});
end

%finding the minimum length of sim0P's
n1 = min(n1_);

%t1:deme indexes
t1 = 0:(p1_(1)-1);


%calculate average sim0P
sim0P_ave = sim0P_{1}(1:n1,:);
for j=1:1:(seeds-1)
    sim0P_ave = sim0P_ave + sim0P_{j+1}(1:n1,:);
end
sim0P_ave = sim0P_ave/seeds;


%===================================================================
%Draw front profile

figure (1);
for i=1:15:n1
    subplot(1,3,1);
    plot(t1,sim0P_ave(i,:));
    xlabel('Deme position');
    ylabel('average Phage per deme');
    %title shows visualization step
    title((i-1)/3);
    subplot(1,3,2);
    plot(t1,sim0P_ave(i+1,:));
    xlabel('Deme position');
    ylabel('average Uninfected bacteria per deme');
    %title shows visualization step
    title((i-1)/3);
    subplot(1,3,3);
    plot(t1,sim0P_ave(i+2,:));
    xlabel('Deme position');
    ylabel('average Infected Bacteria per deme');
    %title shows visualization step
    title((i-1)/3);
    
    pause(.00001);
end


%====================================================================
%Draw front position and heterozygosity, and calculate fit data

% Calculate w:
width_=zeros(1,seeds);
for j=1:1:seeds
    sim0P_temp = sim0P_{j};
    maxi = mean(sim0P_temp(n1-2,deme_strt:deme_end));
    left=0;
    right=0;
    for i=deme_end:1:demes
        if ((sim0P_temp(n1-2,i)>0.5*maxi) && (sim0P_temp(n1-2,i+1)<0.5*maxi))
            left=i;
        end
        if ((sim0P_temp(n1-2,i)>0.05*maxi) && (sim0P_temp(n1-2,i+1)<0.05*maxi))
            right=i;
        end
    end
    width_(j)=right-left;
end


width=mean(width_);
SD2=std(width_);




% calculate Ne2:

x=Ne2start/v_steps;
%A=[sim0H_1(x:p2);sim0H_2(x:p2);sim0H_3(x:p2);sim0H_4(x:p2);sim0H_5(x:p2);sim0H_6(x:p2);sim0H_7(x:p2);sim0H_8(x:p2);sim0H_9(x:p2);sim0H_10(x:p2);sim0H_11(x:p2);sim0H_12(x:p2);sim0H_13(x:p2);sim0H_14(x:p2);sim0H_15(x:p2);sim0H_16(x:p2);sim0H_17(x:p2);sim0H_18(x:p2);sim0H_19(x:p2);sim0H_20(x:p2)];
%digitsold=digits(10);
%S=vpa(10*std(log(A)));
pH2=polyfit(t2(x:p2),log(sim0H_ave(x:p2)),1);

HCal2 = pH2(1)*t2(x:p2) + pH2(2);


% calculate Ne1:

xx=Ne1end/v_steps;
%AA=[sim0H_1(1:xx);sim0H_2(1:xx);sim0H_3(1:xx);sim0H_4(1:xx);sim0H_5(1:xx);sim0H_6(1:xx);sim0H_7(1:xx);sim0H_8(1:xx);sim0H_9(1:xx);sim0H_10(1:xx);sim0H_11(1:xx);sim0H_12(1:xx);sim0H_13(1:xx);sim0H_14(1:xx);sim0H_15(1:xx);sim0H_16(1:xx);sim0H_17(1:xx);sim0H_18(1:xx);sim0H_19(1:xx);sim0H_20(1:xx)];
%digitsold=digits(10);
%S=vpa(10*std(log(AA)));
pH1=polyfit(t2(1:xx),log(sim0H_ave(1:xx)),1);

HCal1 = pH1(1)*t2(1:xx) + pH1(2);


% calculate fixsteps:
fixsteps = (mean(p2_) - 1)*v_steps;


% calculate std of fixsteps:
SD1=std(p2_);


% plot H(t):

figure(2)
scatter(t2(2:p2),log(sim0H_ave(2:p2)));
hold all
plot(t2(x:p2),HCal2);
hold all
plot(t2(1:xx),HCal1);
xlabel('Simulation step beginning from labelling event');
ylabel('log(H(t))');
title('average Heterozygosity of phage over 20 simulations');
grid on;
hold off


% calculate v:

for i=1:1:p5
    if sim0F2_{1}(i)>0
        strt=i;
        break;
    end
end

pF=polyfit(t5(strt:p5),sim0F2_ave(strt:p5)/half_vel,1);

F2Cal = pF(1)*t5(strt:p5)+ pF(2);


% plot v:

figure(3);
scatter(t5(1:p5),sim0F2_ave(1:p5)/half_vel);
hold on
plot(t5(strt:p5),F2Cal);
xlabel('Simulation step from the beginning');
ylabel('position (unit: dx)');
title('Front Position averaged over 20 simulations');
grid on
hold off


%====================================================================
% save figs and outputs

saveas(figure(1),'P_average','jpg');
saveas(figure(2),'H_average','jpg');
saveas(figure(3),'F2_average','jpg');

B = [-2/pH1(1), -2/pH2(1), fixsteps, SD1, pF(1), width, SD2];
save Ne1_Ne2_fixsteps_std_v_w_std.out B -ascii;





