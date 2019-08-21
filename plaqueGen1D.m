load sim001P.dat;
load sim001H.dat;
load sim001L.dat;
load sim001F2.dat;

[n1,p1] = size(sim001P);
t1 = 0:(p1-1);
[n2, p2] = size(sim001H);
t2 = 0:(p2-1);
[n3, p3] = size(sim001L);
t3 = 0:(p3-1);
[n5, p5] = size(sim001F2);
t5 = 0:(p5-1);

% v5 = t5;
% for i=1:1:(p5-1)
%     v5(i)=sim001F2(i+1)-sim001F2(i);
% end
% v5(p5)=v5(p5-1);

figure (1);
for i=1:3:n1
    subplot(1,3,1);
    plot(t1,sim001P(i,:));
    xlabel('Deme position');
    ylabel('Phage per deme');
    %title shows visualization step
    title((i-1)/3);
    subplot(1,3,2);
    plot(t1,sim001P(i+1,:));
    xlabel('Deme position');
    ylabel('Uninfected bacteria per deme');
    %title shows visualization step
    title((i-1)/3);
    subplot(1,3,3);
    plot(t1,sim001P(i+2,:));
    xlabel('Deme position');
    ylabel('Infected Bacteria per deme');
    %title shows visualization step
    title((i-1)/3);
    
    pause(.00001);
end

% figure (2);
% plot(t2,log(sim001H));
% title('Heterozygosity of phage');
% xlabel('Visualization step)');
% ylabel('log(H(t))');

pH=polyfit(t2(2:p2),log(sim001H(2:p2)),1);

HCal = pH(1)*t2(2:p2) + pH(2);

figure(2)
scatter(t2(2:p2),log(sim001H(2:p2)));
hold on
plot(t2(2:p2),HCal);
xlabel('Visualization step after labelling event');
ylabel('log(H(t))');
title('Heterozygosity of phage');
grid on
hold off

% figure (3);
% subplot(1,2,1);
% plot(t5,sim001F2);
% xlabel('Visualization step');
% ylabel('unit: dx');
% title('Front Position');
% subplot(1,2,2);
% plot(t5,v5);
% xlabel('Visualization step');
% ylabel('unit: dx/(dt*visualization_steps)');
% title('Front Velocity');

for i=1:1:p5
    if sim001F2(i)>0
        strt=i;
        break;
    end
end

pF=polyfit(t5(strt:p5),sim001F2(strt:p5),1);

F2Cal = pF(1)*t5(strt:p5)+ pF(2);

figure(3);
scatter(t5,sim001F2);
hold on
plot(t5(strt:p5),F2Cal);
xlabel('Visualization step');
ylabel('position (unit: dx)');
title('Front Position');
grid on
hold off

saveas(figure(1),'001P','jpg');
saveas(figure(2),'001H','jpg');
saveas(figure(3),'001F2','jpg');

save sim001F_fit.out pF -ascii;
save sim001H_fit.out pH -ascii;



