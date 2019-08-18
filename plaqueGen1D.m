load sim001P.dat;
load sim001H.dat;
load sim001L.dat;
%load sim001F1.dat;
load sim001F2.dat;

[n1,p1] = size(sim001P);
t1 = 0:(p1-1);
[n2, p2] = size(sim001H);
t2 = 0:(p2-1);
[n3, p3] = size(sim001L);
t3 = 0:(p3-1);
%[n4, p4] = size(sim001F1);
%t4 = 0:p4-1;
[n5, p5] = size(sim001F2);
t5 = 0:(p5-1);

v5 = t5;
for i=1:1:(p5-1)
    v5(i)=sim001F2(i+1)-sim001F2(i);
end
v5(p5)=v5(p5-1);

figure (1);
for i=1:3:n1
    subplot(1,3,1);
    plot(t1,sim001P(i,:));
    legend('Phage');
    xlabel('Deme position');
    ylabel('Population per deme');
    title((i-1)/3);
    subplot(1,3,2);
    plot(t1,sim001P(i+1,:));
    legend('Uninfected bacteria');
    xlabel('Deme position');
    ylabel('Population per deme');
    title((i-1)/3);
    subplot(1,3,3);
    plot(t1,sim001P(i+2,:));
    legend('Infected Bacteria');
    xlabel('Deme position');
    ylabel('Population per deme');
     title((i-1)/3);
    
    pause(.00001);
end

figure (2);
plot(t2,log(sim001H));
title('Heterozygosity of phage');
xlabel('Visualization step)');
ylabel('log(H(t))');

figure (3);
subplot(1,2,1);
plot(t5,sim001F2);
xlabel('Visualization step');
ylabel('unit: dx');
title('Front Position');
subplot(1,2,2);
plot(t5,v5);
xlabel('Visualization step');
ylabel('unit: dx/(dt*visualization_steps)');
title('Front Velocity');


