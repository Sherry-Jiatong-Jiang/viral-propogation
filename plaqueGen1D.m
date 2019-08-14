load Psim001.dat;
load Hsim001.dat;
load Lsim001.dat;
load F1sim001.dat;
load F2sim001.dat;

[n1,p1] = size(Psim001);
t1 = 1:p1;
[n2, p2] = size(Hsim001);
t2 = 1:p2;
[n3, p3] = size(Lsim001);
t3 = 1:p3;
[n4, p4] = size(F1sim001);
t4 = 1:p4;
[n5, p5] = size(F2sim001);
t5 = 1:p5;
figure (1);
for i=1:3:n1
    subplot(1,3,1);
    plot(t1,Psim001(i,:));
    legend('Phage');
    xlabel('Deme position');
    ylabel('Population per deme');
    title((i-1)/3);
    subplot(1,3,2);
    plot(t1,Psim001(i+1,:));
    legend('Uninfected bacteria');
    xlabel('Deme position');
    ylabel('Population per deme');
    title((i-1)/3);
    subplot(1,3,3);
    plot(t1,Psim001(i+2,:));
    legend('Infected Bacteria');
    xlabel('Deme position');
    ylabel('Population per deme');
     title((i-1)/3);
    
    pause(.001);
end

figure (2);
plot(t2,log(Hsim001));
title('Heterozygosity of phage');
xlabel('Visualization step)');
ylabel('log(H(t))');

figure (3);

% subplot(2,1,1);
plot(t5,F2sim001);
xlabel('Visualization step');
ylabel('unit: dx/dt');
title('Front Position');

% v = F1sim001;
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


