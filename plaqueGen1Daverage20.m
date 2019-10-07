%Designed explicitly for starting_step = 0 with no concatnation, with 20 random seeds, all have reached fixation. 

%input: y (Ne2 starting simulation step after labelling); z (Ne1 ending simulation step after
%labelling); v_steps (visualizaiton_steps); deme_strt, deme_end (between which average
%is taken to calculate max level for width calculation. make sure both are at plateau.); demes (total deme number)
 
%output: -2/pH1(1) (Ne1); -2/pH2(1) (Ne2); fixsteps (fixsteps); SD1 (std of fixsteps); pF(1) (v); width (w); SD2 (std of w).

y=12000;
z=6000;
v_steps=20;
deme_strt=1;
deme_end=50;
demes=100;

load sim0P_1.dat;
load sim0P_2.dat;
load sim0P_3.dat;
load sim0P_4.dat;
load sim0P_5.dat;
load sim0P_6.dat;
load sim0P_7.dat;
load sim0P_8.dat;
load sim0P_9.dat;
load sim0P_10.dat;
load sim0P_11.dat;
load sim0P_12.dat;
load sim0P_13.dat;
load sim0P_14.dat;
load sim0P_15.dat;
load sim0P_16.dat;
load sim0P_17.dat;
load sim0P_18.dat;
load sim0P_19.dat;
load sim0P_20.dat;

load sim0H_1.dat;
load sim0H_2.dat;
load sim0H_3.dat;
load sim0H_4.dat;
load sim0H_5.dat;
load sim0H_6.dat;
load sim0H_7.dat;
load sim0H_8.dat;
load sim0H_9.dat;
load sim0H_10.dat;
load sim0H_11.dat;
load sim0H_12.dat;
load sim0H_13.dat;
load sim0H_14.dat;
load sim0H_15.dat;
load sim0H_16.dat;
load sim0H_17.dat;
load sim0H_18.dat;
load sim0H_19.dat;
load sim0H_20.dat;

% load sim0L_1.dat;
% load sim0L_2.dat;
% load sim0L_3.dat;
% load sim0L_4.dat;
% load sim0L_5.dat;
% load sim0L_6.dat;
% load sim0L_7.dat;
% load sim0L_8.dat;
% load sim0L_9.dat;
% load sim0L_10.dat;
% load sim0L_11.dat;
% load sim0L_12.dat;
% load sim0L_13.dat;
% load sim0L_14.dat;
% load sim0L_15.dat;
% load sim0L_16.dat;
% load sim0L_17.dat;
% load sim0L_18.dat;
% load sim0L_19.dat;
% load sim0L_20.dat;
% 
load sim0F2_1.dat;
load sim0F2_2.dat;
load sim0F2_3.dat;
load sim0F2_4.dat;
load sim0F2_5.dat;
load sim0F2_6.dat;
load sim0F2_7.dat;
load sim0F2_8.dat;
load sim0F2_9.dat;
load sim0F2_10.dat;
load sim0F2_11.dat;
load sim0F2_12.dat;
load sim0F2_13.dat;
load sim0F2_14.dat;
load sim0F2_15.dat;
load sim0F2_16.dat;
load sim0F2_17.dat;
load sim0F2_18.dat;
load sim0F2_19.dat;
load sim0F2_20.dat;

%Keep as 1
half_vel=1;

[n1_1, p1_1] = size(sim0P_1);
[n1_2, p1_2] = size(sim0P_2);
[n1_3, p1_3] = size(sim0P_3);
[n1_4, p1_4] = size(sim0P_4);
[n1_5, p1_5] = size(sim0P_5);
[n1_6, p1_6] = size(sim0P_6);
[n1_7, p1_7] = size(sim0P_7);
[n1_8, p1_8] = size(sim0P_8);
[n1_9, p1_9] = size(sim0P_9);
[n1_10, p1_10] = size(sim0P_10);
[n1_11, p1_11] = size(sim0P_11);
[n1_12, p1_12] = size(sim0P_12);
[n1_13, p1_13] = size(sim0P_13);
[n1_14, p1_14] = size(sim0P_14);
[n1_15, p1_15] = size(sim0P_15);
[n1_16, p1_16] = size(sim0P_16);
[n1_17, p1_17] = size(sim0P_17);
[n1_18, p1_18] = size(sim0P_18);
[n1_19, p1_19] = size(sim0P_19);
[n1_20, p1_20] = size(sim0P_20);

%t1:deme indexes
t1 = 0:(p1_1-1);
n1 = min([n1_1,n1_2,n1_3,n1_4,n1_5,n1_6,n1_7,n1_8,n1_9,n1_10,n1_11,n1_12,n1_13,n1_14,n1_15,n1_16,n1_17,n1_18,n1_19,n1_20]);

[n2_1, p2_1] = size(sim0H_1);
[n2_2, p2_2] = size(sim0H_2);
[n2_3, p2_3] = size(sim0H_3);
[n2_4, p2_4] = size(sim0H_4);
[n2_5, p2_5] = size(sim0H_5);
[n2_6, p2_6] = size(sim0H_6);
[n2_7, p2_7] = size(sim0H_7);
[n2_8, p2_8] = size(sim0H_8);
[n2_9, p2_9] = size(sim0H_9);
[n2_10, p2_10] = size(sim0H_10);
[n2_11, p2_11] = size(sim0H_11);
[n2_12, p2_12] = size(sim0H_12);
[n2_13, p2_13] = size(sim0H_13);
[n2_14, p2_14] = size(sim0H_14);
[n2_15, p2_15] = size(sim0H_15);
[n2_16, p2_16] = size(sim0H_16);
[n2_17, p2_17] = size(sim0H_17);
[n2_18, p2_18] = size(sim0H_18);
[n2_19, p2_19] = size(sim0H_19);
[n2_20, p2_20] = size(sim0H_20);

p2 = max([p2_1,p2_2,p2_3,p2_4,p2_5,p2_6,p2_7,p2_8,p2_9,p2_10,p2_11,p2_12,p2_13,p2_14,p2_15,p2_16,p2_17,p2_18,p2_19,p2_20]);

if p2>p2_1
    sim0H_1=[sim0H_1,zeros(1,p2-p2_1)];
end
if p2>p2_2
    sim0H_2=[sim0H_2,zeros(1,p2-p2_2)];
end
if p2>p2_3
    sim0H_3=[sim0H_3,zeros(1,p2-p2_3)];
end
if p2>p2_4
    sim0H_4=[sim0H_4,zeros(1,p2-p2_4)];
end
if p2>p2_5
    sim0H_5=[sim0H_5,zeros(1,p2-p2_5)];
end
if p2>p2_6
    sim0H_6=[sim0H_6,zeros(1,p2-p2_6)];
end
if p2>p2_7
    sim0H_7=[sim0H_7,zeros(1,p2-p2_7)];
end
if p2>p2_8
    sim0H_8=[sim0H_8,zeros(1,p2-p2_8)];
end
if p2>p2_9
    sim0H_9=[sim0H_9,zeros(1,p2-p2_9)];
end
if p2>p2_10
    sim0H_10=[sim0H_10,zeros(1,p2-p2_10)];
end
if p2>p2_11
    sim0H_11=[sim0H_11,zeros(1,p2-p2_11)];
end
if p2>p2_12
    sim0H_12=[sim0H_12,zeros(1,p2-p2_12)];
end
if p2>p2_13
    sim0H_13=[sim0H_13,zeros(1,p2-p2_13)];
end
if p2>p2_14
    sim0H_14=[sim0H_14,zeros(1,p2-p2_14)];
end
if p2>p2_15
    sim0H_15=[sim0H_15,zeros(1,p2-p2_15)];
end
if p2>p2_16
    sim0H_16=[sim0H_16,zeros(1,p2-p2_16)];
end
if p2>p2_17
    sim0H_17=[sim0H_17,zeros(1,p2-p2_17)];
end
if p2>p2_18
    sim0H_18=[sim0H_18,zeros(1,p2-p2_18)];
end
if p2>p2_19
    sim0H_19=[sim0H_19,zeros(1,p2-p2_19)];
end
if p2>p2_20
    sim0H_20=[sim0H_20,zeros(1,p2-p2_20)];
end

%leaving out the fixation 0s at the end
p2=p2-1;

t2 = linspace(0,v_steps*(p2-1),p2);

% [n3, p3] = size(sim001L_0);
% t3 = 0:(p3-1);


[n5_1, p5_1] = size(sim0F2_1);
[n5_2, p5_2] = size(sim0F2_2);
[n5_3, p5_3] = size(sim0F2_3);
[n5_4, p5_4] = size(sim0F2_4);
[n5_5, p5_5] = size(sim0F2_5);
[n5_6, p5_6] = size(sim0F2_6);
[n5_7, p5_7] = size(sim0F2_7);
[n5_8, p5_8] = size(sim0F2_8);
[n5_9, p5_9] = size(sim0F2_9);
[n5_10, p5_10] = size(sim0F2_10);
[n5_11, p5_11] = size(sim0F2_11);
[n5_12, p5_12] = size(sim0F2_12);
[n5_13, p5_13] = size(sim0F2_13);
[n5_14, p5_14] = size(sim0F2_14);
[n5_15, p5_15] = size(sim0F2_15);
[n5_16, p5_16] = size(sim0F2_16);
[n5_17, p5_17] = size(sim0F2_17);
[n5_18, p5_18] = size(sim0F2_18);
[n5_19, p5_19] = size(sim0F2_19);
[n5_20, p5_20] = size(sim0F2_20);

p5 = min([p5_1,p5_2,p5_3,p5_4,p5_5,p5_6,p5_7,p5_8,p5_9,p5_10,p5_11,p5_12,p5_13,p5_14,p5_15,p5_16,p5_17,p5_18,p5_19,p5_20]);

t5 = linspace(0,v_steps*(p5-1),p5);


figure (1);
for i=1:15:n1
    subplot(1,3,1);
    plot(t1,(sim0P_1(i,:)+sim0P_2(i,:)+sim0P_3(i,:)+sim0P_4(i,:)+sim0P_5(i,:)+sim0P_6(i,:)+sim0P_7(i,:)+sim0P_8(i,:)+sim0P_9(i,:)+sim0P_10(i,:)+sim0P_11(i,:)+sim0P_12(i,:)+sim0P_13(i,:)+sim0P_14(i,:)+sim0P_15(i,:)+sim0P_16(i,:)+sim0P_17(i,:)+sim0P_18(i,:)+sim0P_19(i,:)+sim0P_20(i,:))/20);
    xlabel('Deme position');
    ylabel('average Phage per deme');
    %title shows visualization step
    title((i-1)/3);
    subplot(1,3,2);
    plot(t1,(sim0P_1(i+1,:)+sim0P_2(i+1,:)+sim0P_3(i+1,:)+sim0P_4(i+1,:)+sim0P_5(i+1,:)+sim0P_6(i+1,:)+sim0P_7(i+1,:)+sim0P_8(i+1,:)+sim0P_9(i+1,:)+sim0P_10(i+1,:)+sim0P_11(i+1,:)+sim0P_12(i+1,:)+sim0P_13(i+1,:)+sim0P_14(i+1,:)+sim0P_15(i+1,:)+sim0P_16(i+1,:)+sim0P_17(i+1,:)+sim0P_18(i+1,:)+sim0P_19(i+1,:)+sim0P_20(i+1,:))/20);
    xlabel('Deme position');
    ylabel('average Uninfected bacteria per deme');
    %title shows visualization step
    title((i-1)/3);
    subplot(1,3,3);
    plot(t1,(sim0P_1(i+2,:)+sim0P_2(i+2,:)+sim0P_3(i+2,:)+sim0P_4(i+2,:)+sim0P_5(i+2,:)+sim0P_6(i+2,:)+sim0P_7(i+2,:)+sim0P_8(i+2,:)+sim0P_9(i+2,:)+sim0P_10(i+2,:)+sim0P_11(i+2,:)+sim0P_12(i+2,:)+sim0P_13(i+2,:)+sim0P_14(i+2,:)+sim0P_15(i+2,:)+sim0P_16(i+2,:)+sim0P_17(i+2,:)+sim0P_18(i+2,:)+sim0P_19(i+2,:)+sim0P_20(i+2,:))/20);
    xlabel('Deme position');
    ylabel('average Infected Bacteria per deme');
    %title shows visualization step
    title((i-1)/3);
    
    pause(.00001);
end


% Calculate w:

maxi = mean(sim0P_1(n1-2,deme_strt:deme_end));
left=0;
right=0;
for i=deme_end:1:demes
    if ((sim0P_1(n1-2,i)>0.5*maxi) && (sim0P_1(n1-2,i+1)<0.5*maxi))
        left=i;
    end
    if ((sim0P_1(n1-2,i)>0.05*maxi) && (sim0P_1(n1-2,i+1)<0.05*maxi))
        right=i;
    end
end
width_1=right-left;

maxi = mean(sim0P_2(n1-2,deme_strt:deme_end));
left=0;
right=0;
for i=deme_end:1:demes
    if ((sim0P_2(n1-2,i)>0.5*maxi) && (sim0P_2(n1-2,i+1)<0.5*maxi))
        left=i;
    end
    if ((sim0P_2(n1-2,i)>0.05*maxi) && (sim0P_2(n1-2,i+1)<0.05*maxi))
        right=i;
    end
end
width_2=right-left;

maxi = mean(sim0P_3(n1-2,deme_strt:deme_end));
left=0;
right=0;
for i=deme_end:1:demes
    if ((sim0P_3(n1-2,i)>0.5*maxi) && (sim0P_3(n1-2,i+1)<0.5*maxi))
        left=i;
    end
    if ((sim0P_3(n1-2,i)>0.05*maxi) && (sim0P_3(n1-2,i+1)<0.05*maxi))
        right=i;
    end
end
width_3=right-left;

maxi = mean(sim0P_4(n1-2,deme_strt:deme_end));
left=0;
right=0;
for i=deme_end:1:demes
    if ((sim0P_4(n1-2,i)>0.5*maxi) && (sim0P_4(n1-2,i+1)<0.5*maxi))
        left=i;
    end
    if ((sim0P_4(n1-2,i)>0.05*maxi) && (sim0P_4(n1-2,i+1)<0.05*maxi))
        right=i;
    end
end
width_4=right-left;

maxi = mean(sim0P_5(n1-2,deme_strt:deme_end));
left=0;
right=0;
for i=deme_end:1:demes
    if ((sim0P_5(n1-2,i)>0.5*maxi) && (sim0P_5(n1-2,i+1)<0.5*maxi))
        left=i;
    end
    if ((sim0P_5(n1-2,i)>0.05*maxi) && (sim0P_5(n1-2,i+1)<0.05*maxi))
        right=i;
    end
end
width_5=right-left;

maxi = mean(sim0P_6(n1-2,deme_strt:deme_end));
left=0;
right=0;
for i=deme_end:1:demes
    if ((sim0P_6(n1-2,i)>0.5*maxi) && (sim0P_6(n1-2,i+1)<0.5*maxi))
        left=i;
    end
    if ((sim0P_6(n1-2,i)>0.05*maxi) && (sim0P_6(n1-2,i+1)<0.05*maxi))
        right=i;
    end
end
width_6=right-left;

maxi = mean(sim0P_7(n1-2,deme_strt:deme_end));
left=0;
right=0;
for i=deme_end:1:demes
    if ((sim0P_7(n1-2,i)>0.5*maxi) && (sim0P_7(n1-2,i+1)<0.5*maxi))
        left=i;
    end
    if ((sim0P_7(n1-2,i)>0.05*maxi) && (sim0P_7(n1-2,i+1)<0.05*maxi))
        right=i;
    end
end
width_7=right-left;

maxi = mean(sim0P_8(n1-2,deme_strt:deme_end));
left=0;
right=0;
for i=deme_end:1:demes
    if ((sim0P_8(n1-2,i)>0.5*maxi) && (sim0P_8(n1-2,i+1)<0.5*maxi))
        left=i;
    end
    if ((sim0P_8(n1-2,i)>0.05*maxi) && (sim0P_8(n1-2,i+1)<0.05*maxi))
        right=i;
    end
end
width_8=right-left;

maxi = mean(sim0P_9(n1-2,deme_strt:deme_end));
left=0;
right=0;
for i=deme_end:1:demes
    if ((sim0P_9(n1-2,i)>0.5*maxi) && (sim0P_9(n1-2,i+1)<0.5*maxi))
        left=i;
    end
    if ((sim0P_9(n1-2,i)>0.05*maxi) && (sim0P_9(n1-2,i+1)<0.05*maxi))
        right=i;
    end
end
width_9=right-left;

maxi = mean(sim0P_10(n1-2,deme_strt:deme_end));
left=0;
right=0;
for i=deme_end:1:demes
    if ((sim0P_10(n1-2,i)>0.5*maxi) && (sim0P_10(n1-2,i+1)<0.5*maxi))
        left=i;
    end
    if ((sim0P_10(n1-2,i)>0.05*maxi) && (sim0P_10(n1-2,i+1)<0.05*maxi))
        right=i;
    end
end
width_10=right-left;

maxi = mean(sim0P_11(n1-2,deme_strt:deme_end));
left=0;
right=0;
for i=deme_end:1:demes
    if ((sim0P_11(n1-2,i)>0.5*maxi) && (sim0P_11(n1-2,i+1)<0.5*maxi))
        left=i;
    end
    if ((sim0P_11(n1-2,i)>0.05*maxi) && (sim0P_11(n1-2,i+1)<0.05*maxi))
        right=i;
    end
end
width_11=right-left;

maxi = mean(sim0P_12(n1-2,deme_strt:deme_end));
left=0;
right=0;
for i=deme_end:1:demes
    if ((sim0P_12(n1-2,i)>0.5*maxi) && (sim0P_12(n1-2,i+1)<0.5*maxi))
        left=i;
    end
    if ((sim0P_12(n1-2,i)>0.05*maxi) && (sim0P_12(n1-2,i+1)<0.05*maxi))
        right=i;
    end
end
width_12=right-left;

maxi = mean(sim0P_13(n1-2,deme_strt:deme_end));
left=0;
right=0;
for i=deme_end:1:demes
    if ((sim0P_13(n1-2,i)>0.5*maxi) && (sim0P_13(n1-2,i+1)<0.5*maxi))
        left=i;
    end
    if ((sim0P_13(n1-2,i)>0.05*maxi) && (sim0P_13(n1-2,i+1)<0.05*maxi))
        right=i;
    end
end
width_13=right-left;

maxi = mean(sim0P_14(n1-2,deme_strt:deme_end));
left=0;
right=0;
for i=deme_end:1:demes
    if ((sim0P_14(n1-2,i)>0.5*maxi) && (sim0P_14(n1-2,i+1)<0.5*maxi))
        left=i;
    end
    if ((sim0P_14(n1-2,i)>0.05*maxi) && (sim0P_14(n1-2,i+1)<0.05*maxi))
        right=i;
    end
end
width_14=right-left;

maxi = mean(sim0P_15(n1-2,deme_strt:deme_end));
left=0;
right=0;
for i=deme_end:1:demes
    if ((sim0P_15(n1-2,i)>0.5*maxi) && (sim0P_15(n1-2,i+1)<0.5*maxi))
        left=i;
    end
    if ((sim0P_15(n1-2,i)>0.05*maxi) && (sim0P_15(n1-2,i+1)<0.05*maxi))
        right=i;
    end
end
width_15=right-left;

maxi = mean(sim0P_16(n1-2,deme_strt:deme_end));
left=0;
right=0;
for i=deme_end:1:demes
    if ((sim0P_16(n1-2,i)>0.5*maxi) && (sim0P_16(n1-2,i+1)<0.5*maxi))
        left=i;
    end
    if ((sim0P_16(n1-2,i)>0.05*maxi) && (sim0P_16(n1-2,i+1)<0.05*maxi))
        right=i;
    end
end
width_16=right-left;

maxi = mean(sim0P_17(n1-2,deme_strt:deme_end));
left=0;
right=0;
for i=deme_end:1:demes
    if ((sim0P_17(n1-2,i)>0.5*maxi) && (sim0P_17(n1-2,i+1)<0.5*maxi))
        left=i;
    end
    if ((sim0P_17(n1-2,i)>0.05*maxi) && (sim0P_17(n1-2,i+1)<0.05*maxi))
        right=i;
    end
end
width_17=right-left;

maxi = mean(sim0P_18(n1-2,deme_strt:deme_end));
left=0;
right=0;
for i=deme_end:1:demes
    if ((sim0P_18(n1-2,i)>0.5*maxi) && (sim0P_18(n1-2,i+1)<0.5*maxi))
        left=i;
    end
    if ((sim0P_18(n1-2,i)>0.05*maxi) && (sim0P_18(n1-2,i+1)<0.05*maxi))
        right=i;
    end
end
width_18=right-left;

maxi = mean(sim0P_19(n1-2,deme_strt:deme_end));
left=0;
right=0;
for i=deme_end:1:demes
    if ((sim0P_19(n1-2,i)>0.5*maxi) && (sim0P_19(n1-2,i+1)<0.5*maxi))
        left=i;
    end
    if ((sim0P_19(n1-2,i)>0.05*maxi) && (sim0P_19(n1-2,i+1)<0.05*maxi))
        right=i;
    end
end
width_19=right-left;

maxi = mean(sim0P_20(n1-2,deme_strt:deme_end));
left=0;
right=0;
for i=deme_end:1:demes
    if ((sim0P_20(n1-2,i)>0.5*maxi) && (sim0P_20(n1-2,i+1)<0.5*maxi))
        left=i;
    end
    if ((sim0P_20(n1-2,i)>0.05*maxi) && (sim0P_20(n1-2,i+1)<0.05*maxi))
        right=i;
    end
end
width_20=right-left;


width=mean([width_1,width_2,width_3,width_4,width_5,width_6,width_7,width_8,width_9,width_10,width_11,width_12,width_13,width_14,width_15,width_16,width_17,width_18,width_19,width_20]);
SD2=std([width_1,width_2,width_3,width_4,width_5,width_6,width_7,width_8,width_9,width_10,width_11,width_12,width_13,width_14,width_15,width_16,width_17,width_18,width_19,width_20]);


% calculate Ne2:

x=y/v_steps;
%A=[sim0H_1(x:p2);sim0H_2(x:p2);sim0H_3(x:p2);sim0H_4(x:p2);sim0H_5(x:p2);sim0H_6(x:p2);sim0H_7(x:p2);sim0H_8(x:p2);sim0H_9(x:p2);sim0H_10(x:p2);sim0H_11(x:p2);sim0H_12(x:p2);sim0H_13(x:p2);sim0H_14(x:p2);sim0H_15(x:p2);sim0H_16(x:p2);sim0H_17(x:p2);sim0H_18(x:p2);sim0H_19(x:p2);sim0H_20(x:p2)];
%digitsold=digits(10);
%S=vpa(10*std(log(A)));
pH2=polyfit(t2(x:p2),log((sim0H_1(x:p2)+sim0H_2(x:p2)+sim0H_3(x:p2)+sim0H_4(x:p2)+sim0H_5(x:p2)+sim0H_6(x:p2)+sim0H_7(x:p2)+sim0H_8(x:p2)+sim0H_9(x:p2)+sim0H_10(x:p2)+sim0H_11(x:p2)+sim0H_12(x:p2)+sim0H_13(x:p2)+sim0H_14(x:p2)+sim0H_15(x:p2)+sim0H_16(x:p2)+sim0H_17(x:p2)+sim0H_18(x:p2)+sim0H_19(x:p2)+sim0H_20(x:p2))/20),1);

HCal2 = pH2(1)*t2(x:p2) + pH2(2);


% calculate Ne1:

xx=z/v_steps;
%AA=[sim0H_1(1:xx);sim0H_2(1:xx);sim0H_3(1:xx);sim0H_4(1:xx);sim0H_5(1:xx);sim0H_6(1:xx);sim0H_7(1:xx);sim0H_8(1:xx);sim0H_9(1:xx);sim0H_10(1:xx);sim0H_11(1:xx);sim0H_12(1:xx);sim0H_13(1:xx);sim0H_14(1:xx);sim0H_15(1:xx);sim0H_16(1:xx);sim0H_17(1:xx);sim0H_18(1:xx);sim0H_19(1:xx);sim0H_20(1:xx)];
%digitsold=digits(10);
%S=vpa(10*std(log(AA)));
pH1=polyfit(t2(1:xx),log((sim0H_1(1:xx)+sim0H_2(1:xx)+sim0H_3(1:xx)+sim0H_4(1:xx)+sim0H_5(1:xx)+sim0H_6(1:xx)+sim0H_7(1:xx)+sim0H_8(1:xx)+sim0H_9(1:xx)+sim0H_10(1:xx)+sim0H_11(1:xx)+sim0H_12(1:xx)+sim0H_13(1:xx)+sim0H_14(1:xx)+sim0H_15(1:xx)+sim0H_16(1:xx)+sim0H_17(1:xx)+sim0H_18(1:xx)+sim0H_19(1:xx)+sim0H_20(1:xx))/20),1);

HCal1 = pH1(1)*t2(1:xx) + pH1(2);


% calculate fixsteps:
fixsteps = ((p2_1+p2_2+p2_3+p2_4+p2_5+p2_6+p2_7+p2_8+p2_9+p2_10+p2_11+p2_12+p2_13+p2_14+p2_15+p2_16+p2_17+p2_18+p2_19+p2_20) / 20 - 1)*v_steps;

% calculate std of fixsteps:
SD1=std([p2_1,p2_2,p2_3,p2_4,p2_5,p2_6,p2_7,p2_8,p2_9,p2_10,p2_11,p2_12,p2_13,p2_14,p2_15,p2_16,p2_17,p2_18,p2_19,p2_20]);

% plot H(t):

figure(2)
scatter(t2(2:p2),log((sim0H_1(2:p2)+sim0H_2(2:p2)+sim0H_3(2:p2)+sim0H_4(2:p2)+sim0H_5(2:p2)+sim0H_6(2:p2)+sim0H_7(2:p2)+sim0H_8(2:p2)+sim0H_9(2:p2)+sim0H_10(2:p2)+sim0H_11(2:p2)+sim0H_12(2:p2)+sim0H_13(2:p2)+sim0H_14(2:p2)+sim0H_15(2:p2)+sim0H_16(2:p2)+sim0H_17(2:p2)+sim0H_18(2:p2)+sim0H_19(2:p2)+sim0H_20(2:p2))/20));
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
    if sim0F2_1(i)>0
        strt=i;
        break;
    end
end

pF=polyfit(t5(strt:p5),(sim0F2_1(strt:p5)+sim0F2_2(strt:p5)+sim0F2_3(strt:p5)+sim0F2_4(strt:p5)+sim0F2_5(strt:p5)+sim0F2_6(strt:p5)+sim0F2_7(strt:p5)+sim0F2_8(strt:p5)+sim0F2_9(strt:p5)+sim0F2_10(strt:p5)+sim0F2_11(strt:p5)+sim0F2_12(strt:p5)+sim0F2_13(strt:p5)+sim0F2_14(strt:p5)+sim0F2_15(strt:p5)+sim0F2_16(strt:p5)+sim0F2_17(strt:p5)+sim0F2_18(strt:p5)+sim0F2_19(strt:p5)+sim0F2_20(strt:p5))/20/half_vel,1);

F2Cal = pF(1)*t5(strt:p5)+ pF(2);


% plot v:

figure(3);
scatter(t5(1:p5),(sim0F2_1(1:p5)+sim0F2_2(1:p5)+sim0F2_3(1:p5)+sim0F2_4(1:p5)+sim0F2_5(1:p5)+sim0F2_6(1:p5)+sim0F2_7(1:p5)+sim0F2_8(1:p5)+sim0F2_9(1:p5)+sim0F2_10(1:p5)+sim0F2_11(1:p5)+sim0F2_12(1:p5)+sim0F2_13(1:p5)+sim0F2_14(1:p5)+sim0F2_15(1:p5)+sim0F2_16(1:p5)+sim0F2_17(1:p5)+sim0F2_18(1:p5)+sim0F2_19(1:p5)+sim0F2_20(1:p5))/20/half_vel);
hold on
plot(t5(strt:p5),F2Cal);
xlabel('Simulation step from the beginning');
ylabel('position (unit: dx)');
title('Front Position averaged over 20 simulations');
grid on
hold off


% save figs and data

saveas(figure(1),'P_average','jpg');
saveas(figure(2),'H_average','jpg');
saveas(figure(3),'F2_average','jpg');

B = [-2/pH1(1), -2/pH2(1), fixsteps, SD1, pF(1), width, SD2];
save Ne1_Ne2_fixsteps_std_v_w_std.out B -ascii;





