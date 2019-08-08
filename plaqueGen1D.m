load Bsim001.dat
load Bsim001.dat
load Psim001.dat
load Isim001.dat
load Hsim001.dat
[n1,p1] = size(Bsim001)
t1 = 1:p1
[n2, p2] = size(Hsim001)
t2 = 1:p2
figure (1)
for i=1:1:n1
    subplot(1,3,1);
    plot(t1,Psim001(i,:));
    legend('Phage')
    xlabel('Deme posiiton')
    ylabel('Population per deme')
    title(i)
    subplot(1,3,2);
    plot(t1,Bsim001(i,:));
    legend('Uninfected bacteria')
    xlabel('Deme posiiton')
    ylabel('Population per deme')
    title(i)
    subplot(1,3,3);
    plot(t1,Isim001(i,:));
    legend('Infected Bacteria')
    xlabel('Deme posiiton')
    ylabel('Population per deme')
    title(i)
    pause(.003)
end

figure (2)
plot(t2,log(Hsim001(:)));
title('Heterozygosity of phage')
xlabel('Simulation Time (/5)')
ylabel('log(H(t))')
