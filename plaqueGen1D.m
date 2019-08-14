load sim001P.dat;
load sim001H.dat;
load sim001L.dat;
load sim001F1.dat;
load sim001F2.dat;

[n1,p1] = size(sim001P);
t1 = 1:p1;
[n2, p2] = size(sim001H);
t2 = 1:p2;
[n3, p3] = size(sim001L);
t3 = 1:p3;
[n4, p4] = size(sim001F1);
t4 = 1:p4;
[n5, p5] = size(sim001F2);
t5 = 1:p5;
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
    
    pause(.001);
end

figure (2);
plot(t2,log(sim001H));
title('Heterozygosity of phage');
xlabel('Visualization step)');
ylabel('log(H(t))');

figure (3);

% subplot(2,1,1);
plot(t5,sim001F2);
xlabel('Visualization step');
ylabel('unit: dx/dt');
title('Front Position');

% v = sim001F1;
% w =
% for i=1:1:n4
%     for j=v(i):1:v(i+1)
%         v(j) = 1/(v(i+1) - v(i));
%     end
% end
% subplot(2,1,2);
% plot(t4,v);
% xlabel('Simulation step)');
% ylabel('unit: dx/dt');
% title('Front Velocity');


