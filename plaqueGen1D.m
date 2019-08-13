load Psim001.dat;
%load Hsim001.dat;
%load Lsim001.dat;
[n1,p1] = size(Psim001);
t1 = 1:p1;
[n2, p2] = size(Hsim001);
t2 = 1:p2;
figure (1);
for i=1:3:n1
    subplot(1,3,1);
    plot(t1,Psim001(i,:));
    legend('Phage');
    xlabel('Deme posiiton');
    ylabel('Population per deme');
    title((i-1)/3);
    subplot(1,3,2);
    plot(t1,Psim001(i+1,:));
    legend('Uninfected bacteria');
    xlabel('Deme posiiton');
    ylabel('Population per deme');
    title((i-1)/3);
    subplot(1,3,3);
    plot(t1,Psim001(i+2,:));
    legend('Infected Bacteria');
    xlabel('Deme posiiton');
    ylabel('Population per deme');
     title((i-1)/3);
    
    pause(.001);
end

figure (2) ;
plot(t2,log(Hsim001));
title('Heterozygosity of phage');
xlabel('Visualization step)');
ylabel('log(H(t))');

