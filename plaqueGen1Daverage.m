load sim001P_0.dat;
load sim001P_1.dat;
load sim001P_2.dat;
load sim001P_3.dat;
load sim001P_4.dat;

load sim001H_0.dat;
load sim001H_1.dat;
load sim001H_2.dat;
load sim001H_3.dat;
load sim001H_4.dat;

load sim001L_0.dat;
load sim001L_1.dat;
load sim001L_2.dat;
load sim001L_3.dat;
load sim001L_4.dat;

load sim001F2_0.dat;
load sim001F2_1.dat;
load sim001F2_2.dat;
load sim001F2_3.dat;
load sim001F2_4.dat;

[n1_0,p1_0] = size(sim001P_0);
[n1_1,p1_1] = size(sim001P_1);
[n1_2,p1_2] = size(sim001P_2);
[n1_3,p1_3] = size(sim001P_3);
[n1_4,p1_4] = size(sim001P_4);

t1 = 0:(p1_0-1);
n1 = min([n1_0,n1_1,n1_2,n1_3,n1_4]);

[n2_0, p2_0] = size(sim001H_0);
[n2_1, p2_1] = size(sim001H_1);
[n2_2, p2_2] = size(sim001H_2);
[n2_3, p2_3] = size(sim001H_3);
[n2_4, p2_4] = size(sim001H_4);

p2 = min([p2_0,p2_1,p2_2,p2_3,p2_4]);
t2 = 0:(p2-1);

[n3, p3] = size(sim001L_0);
t3 = 0:(p3-1);

[n5_0, p5_0] = size(sim001F2_0);
[n5_1, p5_1] = size(sim001F2_1);
[n5_2, p5_2] = size(sim001F2_2);
[n5_3, p5_3] = size(sim001F2_3);
[n5_4, p5_4] = size(sim001F2_4);

p5 = min([p5_0,p5_1,p5_2,p5_3,p5_4]);
t5 = 0:(p5-1);


figure (1);
for i=1:3:n1
    subplot(1,3,1);
    plot(t1,(sim001P_0(i,:)+sim001P_1(i,:)+sim001P_2(i,:)+sim001P_3(i,:)+sim001P_4(i,:))/5);
    xlabel('Deme position');
    ylabel('average Phage per deme');
    %title shows visualization step
    title((i-1)/3);
    subplot(1,3,2);
    plot(t1,(sim001P_0(i+1,:)+sim001P_1(i+1,:)+sim001P_2(i+1,:)+sim001P_3(i+1,:)+sim001P_4(i+1,:))/5);
    xlabel('Deme position');
    ylabel('average Uninfected bacteria per deme');
    %title shows visualization step
    title((i-1)/3);
    subplot(1,3,3);
    plot(t1,(sim001P_0(i+2,:)+sim001P_1(i+2,:)+sim001P_2(i+2,:)+sim001P_3(i+2,:)+sim001P_4(i+2,:))/5);
    xlabel('Deme position');
    ylabel('average Infected Bacteria per deme');
    %title shows visualization step
    title((i-1)/3);
    
    pause(.00001);
end

x=15;
pH=polyfit(t2(x:p2),log((sim001H_0(x:p2)+sim001H_1(x:p2)+sim001H_2(x:p2)+sim001H_3(x:p2)+sim001H_4(x:p2))/5),1);

HCal = pH(1)*t2(x:p2) + pH(2);

figure(2)
scatter(t2(2:p2),log((sim001H_0(2:p2)+sim001H_1(2:p2)+sim001H_2(2:p2)+sim001H_3(2:p2)+sim001H_4(2:p2))/5));
hold on
plot(t2(x:p2),HCal);
xlabel('Visualization step after labelling event');
ylabel('log(H(t))');
title('average Heterozygosity of phage');
grid on
hold off


for i=1:1:p5
    if sim001F2_0(i)>0
        strt=i;
        break;
    end
end

pF=polyfit(t5(strt:p5),(sim001F2_0(strt:p5)+sim001F2_1(strt:p5)+sim001F2_2(strt:p5)+sim001F2_3(strt:p5)+sim001F2_4(strt:p5))/5,1);

F2Cal = pF(1)*t5(strt:p5)+ pF(2);

figure(3);
scatter(t5(1:p5),(sim001F2_0(1:p5)+sim001F2_1(1:p5)+sim001F2_2(1:p5)+sim001F2_3(1:p5)+sim001F2_4(1:p5))/5);
hold on
plot(t5(strt:p5),F2Cal);
xlabel('Visualization step');
ylabel('position (unit: dx)');
title('average Front Position');
grid on
hold off

saveas(figure(1),'001P_average','jpg');
saveas(figure(2),'001H_average','jpg');
saveas(figure(3),'001F2_average','jpg');

save sim001F_fit_average.out pF -ascii;
save sim001H_fit_average.out pH -ascii;



