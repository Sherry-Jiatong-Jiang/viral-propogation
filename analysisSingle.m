%==============================================================================================
%Inputs required: Nestart and Neend. Ne is then fitted to data between Nestart and Neend steps. 
%Both Nestart and Neend are counted by "visualization step beginning from
%labelling event" (consistent with the graph axis). 
%The values can be estimated from the graph after initial trial run.
%Note that this is slightly different from analysisAverage.m where the axis
%is shown by "simulation step beginning from labelling event".

%Outputs: Velocity and Ne fitting results.

%Specify input here:
Nestart=50;
Neend=100;

%===============================================================
%Load data

load sim0P.dat;
load sim0H.dat;
load sim0L.dat;
load sim0F2.dat;

[n1,p1] = size(sim0P);
t1 = 0:(p1-1);
[n2, p2] = size(sim0H);
t2 = 0:(p2-1);
[n3, p3] = size(sim0L);
t3 = 0:(p3-1);
[n5, p5] = size(sim0F2);
t5 = 0:(p5-1);

%===============================================================
%Plot front profile

figure (1);
for i=1:3:n1
    subplot(1,3,1);
    plot(t1,sim0P(i,:));
    xlabel('Deme position');
    ylabel('Phage per deme');
    %title shows visualization step
    title((i-1)/3);
    subplot(1,3,2);
    plot(t1,sim0P(i+1,:));
    xlabel('Deme position');
    ylabel('Uninfected bacteria per deme');
    %title shows visualization step
    title((i-1)/3);
    subplot(1,3,3);
    plot(t1,sim0P(i+2,:));
    xlabel('Deme position');
    ylabel('Infected Bacteria per deme');
    %title shows visualization step
    title((i-1)/3);
    
    pause(.00001);
end

%==================================================================
%plot heterozygosity and fitting line

reach=0;
if sim0H(p2) == 0
    p2 = p2-1;
    reach=1;
end


pH=polyfit(t2(2:p2),log(sim0H(2:p2)),1);

HCal = pH(1)*t2(2:p2) + pH(2);

figure(2)
%plot from the second data point
scatter(t2(2:p2),log(sim0H(2:p2)));
hold on
plot(t2(2:p2),HCal);
xlabel('Visualization step after labelling event');
ylabel('log(H(t))');
if reach == 1
    title('Heterozygosity of phage (reaches fixation)');
else
    title('Heterozygosity of phage (hasnt reach fixation, data invalid)');
end
grid on
hold off


%==================================================================
%plot front position and fitting line

for i=1:1:p5
    if sim0F2(i)>0
        strt=i;
        break;
    end
end

pF=polyfit(t5(strt:p5),sim0F2(strt:p5),1);

F2Cal = pF(1)*t5(strt:p5)+ pF(2);


figure(3);
scatter(t5,sim0F2);
hold on
plot(t5(strt:p5),F2Cal);
xlabel('Visualization step');
ylabel('position (unit: dx)');
title('Front Position');
grid on
hold off

%==================================================================
%save figures and fitting data

saveas(figure(1),'001P','jpg');
saveas(figure(2),'001H','jpg');
saveas(figure(3),'001F2','jpg');

save sim0F_fit.out pF -ascii;
save sim0H_fit.out pH -ascii;



