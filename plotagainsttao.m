%==========================================================================
%This is the final step after "Ne1_Ne2_fixsteps_std_v_w_std.out" files have
%been collected from all sets of jobs with different parameters. i.e.
%only need to plot results against different parameters.

%This is a template for plotting results against different values of tao.
%Modify this template to get other plots against burst_size and infection rate.
%(Modify array names, file indexes, and plot labels).

%Only use this code after "Ne1_Ne2_fixsteps_std_v_w_std.out" files from
%different job folders have been copied into the same folder as this matlab
%file, and renamed into set1.out, set2.out, set3.out.....and so on.
%Parameter settings of each index should be memorized.

%========================= Specify Inputs =================================
%Specify variable parameter ranges

tao = [10,20,50,100,300];

%Specify relevant file indexes: 
%setm1.out to setn1.out correspond to the
%above tao values, with MESR infection scheme;
%setm2.out to setn2.out correspond to the
%above tao values, with SESR infection scheme;
%setm3.out to setn3.out correspond to the
%above tao values, with MEMR infection scheme;

m1=1;
n1=5;
m2=6;
n2=10;
m3=11;
n3=15;

%========================= Load data into array variables =================

%load data into arrays: tao_Ne1_MESR, tao_Ne1_SESR, tao_Ne1_MEMR

sets=cell(n1-m1+1,1);
for i=m1:1:n1
    sets{i-m1+1} = load(sprintf('set%d.out',i));
end
tao_Ne1_MESR = zeros(1,n1-m1+1);
for i=1:1:n1-m1+1
    tao_Ne1_MESR(i)= sets{i}(1);
end



sets=cell(n2-m2+1,1);
for i=m2:1:n2
    sets{i-m2+1} = load(sprintf('set%d.out',i));
end
tao_Ne1_SESR = zeros(1,n2-m2+1);
for i=1:1:n2-m2+1
    tao_Ne1_SESR(i)= sets{i}(1);
end



sets=cell(n3-m3+1,1);
for i=m3:1:n3
    sets{i-m3+1} = load(sprintf('set%d.out',i));
end
tao_Ne1_MEMR = zeros(1,n3-m3+1);
for i=1:1:n3-m3+1
    tao_Ne1_MEMR(i)= sets{i}(1);
end



%==========================================================================

%load data into arrays: tao_Ne2_MESR, tao_Ne2_SESR, tao_Ne2_MEMR

sets=cell(n1-m1+1,1);
for i=m1:1:n1
    sets{i-m1+1} = load(sprintf('set%d.out',i));
end
tao_Ne2_MESR = zeros(1,n1-m1+1);
for i=1:1:n1-m1+1
    tao_Ne2_MESR(i)= sets{i}(2);
end



sets=cell(n2-m2+1,1);
for i=m2:1:n2
    sets{i-m2+1} = load(sprintf('set%d.out',i));
end
tao_Ne2_SESR = zeros(1,n2-m2+1);
for i=1:1:n2-m2+1
    tao_Ne2_SESR(i)= sets{i}(2);
end




sets=cell(n3-m3+1,1);
for i=m3:1:n3
    sets{i-m3+1} = load(sprintf('set%d.out',i));
end
tao_Ne2_MEMR = zeros(1,n3-m3+1);
for i=1:1:n3-m3+1
    tao_Ne2_MEMR(i)= sets{i}(2);
end


%==========================================================================

%load data into arrays: tao_fixsteps_MESR, tao_fixsteps_SESR, tao_fixsteps_MEMR

sets=cell(n1-m1+1,1);
for i=m1:1:n1
    sets{i-m1+1} = load(sprintf('set%d.out',i));
end
tao_fixsteps_MESR = zeros(1,n1-m1+1);
for i=1:1:n1-m1+1
    tao_fixsteps_MESR(i)= sets{i}(3);
end



sets=cell(n2-m2+1,1);
for i=m2:1:n2
    sets{i-m2+1} = load(sprintf('set%d.out',i));
end
tao_fixsteps_SESR = zeros(1,n2-m2+1);
for i=1:1:n2-m2+1
    tao_fixsteps_SESR(i)= sets{i}(3);
end



sets=cell(n3-m3+1,1);
for i=m3:1:n3
    sets{i-m3+1} = load(sprintf('set%d.out',i));
end
tao_fixsteps_MEMR = zeros(1,n3-m3+1);
for i=1:1:n3-m3+1
    tao_fixsteps_MEMR(i)= sets{i}(3);
end


%==========================================================================

%load data into arrays: tao_fixstepsstd_MESR, tao_fixstepsstd_SESR, tao_fixstepsstd_MEMR

sets=cell(n1-m1+1,1);
for i=m1:1:n1
    sets{i-m1+1} = load(sprintf('set%d.out',i));
end
tao_fixstepsstd_MESR = zeros(1,n1-m1+1);
for i=1:1:n1-m1+1
    tao_fixstepsstd_MESR(i)= sets{i}(4);
end



sets=cell(n2-m2+1,1);
for i=m2:1:n2
    sets{i-m2+1} = load(sprintf('set%d.out',i));
end
tao_fixstepsstd_SESR = zeros(1,n2-m2+1);
for i=1:1:n2-m2+1
    tao_fixstepsstd_SESR(i)= sets{i}(4);
end



sets=cell(n3-m3+1,1);
for i=m3:1:n3
    sets{i-m3+1} = load(sprintf('set%d.out',i));
end
tao_fixstepsstd_MEMR = zeros(1,n3-m3+1);
for i=1:1:n3-m3+1
    tao_fixstepsstd_MEMR(i)= sets{i}(4);
end



%==========================================================================

%load data into arrays: tao_v_MESR, tao_v_SESR, tao_v_MEMR

sets=cell(n1-m1+1,1);
for i=m1:1:n1
    sets{i-m1+1} = load(sprintf('set%d.out',i));
end
tao_v_MESR = zeros(1,n1-m1+1);
for i=1:1:n1-m1+1
    tao_v_MESR(i)= sets{i}(5);
end



sets=cell(n2-m2+1,1);
for i=m2:1:n2
    sets{i-m2+1} = load(sprintf('set%d.out',i));
end
tao_v_SESR = zeros(1,n2-m2+1);
for i=1:1:n2-m2+1
    tao_v_SESR(i)= sets{i}(5);
end



sets=cell(n3-m3+1,1);
for i=m3:1:n3
    sets{i-m3+1} = load(sprintf('set%d.out',i));
end
tao_v_MEMR = zeros(1,n3-m3+1);
for i=1:1:n3-m3+1
    tao_v_MEMR(i)= sets{i}(5);
end



%==========================================================================

%load data into arrays: tao_w_MESR, tao_w_SESR, tao_w_MEMR

sets=cell(n1-m1+1,1);
for i=m1:1:n1
    sets{i-m1+1} = load(sprintf('set%d.out',i));
end
tao_w_MESR = zeros(1,n1-m1+1);
for i=1:1:n1-m1+1
    tao_w_MESR(i)= sets{i}(6);
end




sets=cell(n2-m2+1,1);
for i=m2:1:n2
    sets{i-m2+1} = load(sprintf('set%d.out',i));
end
tao_w_SESR = zeros(1,n2-m2+1);
for i=1:1:n2-m2+1
    tao_w_SESR(i)= sets{i}(6);
end



sets=cell(n3-m3+1,1);
for i=m3:1:n3
    sets{i-m3+1} = load(sprintf('set%d.out',i));
end
tao_w_MEMR = zeros(1,n3-m3+1);
for i=1:1:n3-m3+1
    tao_w_MEMR(i)= sets{i}(6);
end



%==========================================================================

%load data into arrays: tao_wstd_MESR, tao_wstd_SESR, tao_wstd_MEMR

sets=cell(n1-m1+1,1);
for i=m1:1:n1
    sets{i-m1+1} = load(sprintf('set%d.out',i));
end
tao_wstd_MESR = zeros(1,n1-m1+1);
for i=1:1:n1-m1+1
    tao_wstd_MESR(i)= sets{i}(7);
end


sets=cell(n2-m2+1,1);
for i=m2:1:n2
    sets{i-m2+1} = load(sprintf('set%d.out',i));
end
tao_wstd_SESR = zeros(1,n2-m2+1);
for i=1:1:n2-m2+1
    tao_wstd_SESR(i)= sets{i}(7);
end


sets=cell(n3-m3+1,1);
for i=m3:1:n3
    sets{i-m3+1} = load(sprintf('set%d.out',i));
end
tao_wstd_MEMR = zeros(1,n3-m3+1);
for i=1:1:n3-m3+1
    tao_wstd_MEMR(i)= sets{i}(7);
end



%======================== Plot results with array variables ===============

figure(1)
plt(1)=plot(log(tao),log(tao_Ne1_MESR));
hold on
plt(2)=plot(log(tao),log(tao_Ne1_SESR));
hold on
plt(3)=plot(log(tao),log(tao_Ne1_MEMR));
xlabel('log(tao)')
ylabel('log(Ne1)');
legend([plt(1),plt(2),plt(3)], {'Multiple entry single release','Single entry single release (PDE assumption)', 'Multiple entry multiple release (co-infection)'})
title('Early Ne vs lysis time, under different infection schemes');


saveas(figure(1),'Ne1-tao','jpg');


figure(2)
plt(4)=plot(log(tao),log(tao_Ne2_MESR));
hold on
plt(5)=plot(log(tao),log(tao_Ne2_SESR));
hold on
plt(6)=plot(log(tao),log(tao_Ne2_MEMR));
xlabel('log(tao)')
ylabel('log(Ne2)');
legend([plt(4),plt(5),plt(6)], {'Multiple entry single release','Single entry single release (PDE assumption)', 'Multiple entry multiple release (co-infection)'})
title('Late Ne vs lysis time, under different infection schemes');
             

saveas(figure(2),'Ne2-tao','jpg');

figure(3)
plt(7)=errorbar(log(tao),log(tao_fixsteps_MESR),log(tao_fixsteps_MESR + tao_fixstepsstd_MESR)-log(tao_fixsteps_MESR));
hold on
plt(8)=errorbar(log(tao),log(tao_fixsteps_SESR),log(tao_fixsteps_SESR + tao_fixstepsstd_SESR)-log(tao_fixsteps_SESR));
hold on
plt(9)=errorbar(log(tao),log(tao_fixsteps_MEMR),log(tao_fixsteps_MEMR + tao_fixstepsstd_MEMR)-log(tao_fixsteps_MEMR));
xlabel('log(tao)')
ylabel('log(fixation step)');
legend([plt(7),plt(8),plt(9)], {'Multiple entry single release','Single entry single release (PDE assumption)', 'Multiple entry multiple release (co-infection)'})
title('Fixation step vs lysis time, under different infection schemes');


saveas(figure(3),'fixstep-tao','jpg');


figure(4)
plt(10)=plot(log(tao),log(tao_v_MESR));
hold on
plt(11)=plot(log(tao),log(tao_v_SESR));
hold on
plt(12)=plot(log(tao),log(tao_v_MEMR));
xlabel('log(tao)')
ylabel('log(v))');
legend([plt(10),plt(11),plt(12)], {'Multiple entry single release','Single entry single release (PDE assumption)', 'Multiple entry multiple release (co-infection)'})
title('Front velocity vs lysis time, under different infection schemes');


saveas(figure(4),'v-tao','jpg');


figure(5)
plt(13)=errorbar(log(tao),log(tao_w_MESR),log(tao_w_MESR + tao_wstd_MESR)-log(tao_w_MESR));
hold on
plt(14)=errorbar(log(tao),log(tao_w_SESR),log(tao_w_MESR + tao_wstd_SESR)-log(tao_w_SESR));
hold on
plt(15)=errorbar(log(tao),log(tao_w_MEMR),log(tao_w_MESR + tao_wstd_MEMR)-log(tao_w_MEMR));
xlabel('log(tao)')
ylabel('log(w)');
legend([plt(13),plt(14),plt(15)], {'Multiple entry single release','Single entry single release (PDE assumption)', 'Multiple entry multiple release (co-infection)'})
title('Front width vs lysis time, under different infection schemes');


saveas(figure(5),'w-tao','jpg');

