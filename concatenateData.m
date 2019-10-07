%inputs: selected checkpoint; visualization_Steps; labelling_step.

j=4000;
v_steps=20;
l_step=2000;

%load starting data

load sim0H.dat
load sim0P.dat
load sim0L.dat
load sim0F2.dat

%load checkpoint data

simHdat = sprintf('sim%dH.dat', j);
simPdat = sprintf('sim%dP.dat', j);
simF2dat = sprintf('sim%dF2.dat', j);
simLdat = sprintf('sim%dL.dat', j);

simH=load (simHdat);
simP=load (simPdat);
simL=load (simLdat);
simF2=load (simF2dat);

%truncate starting data and append checkpoint data

[n1,p1] = size(simP);
t1 = 0:(p1-1);
[n2, p2] = size(simH);
t2 = 0:(p2-1);
[n3, p3] = size(simL);
t3 = 0:(p3-1);
[n5, p5] = size(simF2);
t5 = 0:(p5-1);

new0P = [sim0P(1:j/v_steps+1,:);simP]; 
new0F2 = [sim0F2(1:j/v_steps+1),simF2]; 

if j >= l_step
    new0H = [sim0H(1:(j-l_step)/v_steps+1),simH];
elseif ((j < l_step)&&(j + v_steps * p2 >= l_step))
    new0H = simH;
else
end

if j >= l_step
    new0L = [sim0L(1:(j-l_step)/v_steps+1,:);simL];
elseif ((j < l_step)&&(j + v_steps * p2 >= l_step))
    new0L = simL;
else
end

%show graphs of H(t) and front position, and delete used checkpoint data

figure(1)
[n6,p6]=size(new0H);
t6=0:(p6-1);
scatter(t6,log(new0H));

figure(2)
[n7,p7]=size(new0F2);
t7=0:(p7-1);
scatter(t7,new0F2);

delete(simHdat);
delete(simPdat);
delete(simF2dat);
delete(simLdat);

%save concatenated data to starting data

save sim0H.dat new0H -ascii;
save sim0P.dat new0P -ascii;
save sim0F2.dat new0F2 -ascii;
save sim0L.dat new0L -ascii;