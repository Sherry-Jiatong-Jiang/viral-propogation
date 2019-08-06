function [ B,P,I,avv,avw ] = plaqueGen( alpha,L,beta,D,P0,Pstart,B0)
%this function simulates the phage-bacteria
%dynamics in a 2D plaque. Discretized PDE system. No stochasticity is included

%PARAMETERS:
%alpha adsorption rate
%L lysis time
%beta burst size
%D diffusion rate
%P0 initial phage density
%Pstart initial radius of phage droplet
%B0 initial bacterial density


dx=sqrt(1000);  %lattice size (in um)
dt=1; %time interval (1 min)
x=(-80:80);
box=numel(x);
[X,Y]=meshgrid(x,x); %define spatial grid
Tmax=1000;
K=10^5; %%bacteria carrying capacity per lattice site 
%Bmax=B0;
%Pmax=beta*Bmax;
%%follow the dynamics of free phage (P), bacteria (B) and infected cells
%%(I)

%%define variables
B=zeros([box,box,Tmax+1]);
P=zeros([box,box,Tmax+1]);
I=zeros([box,box,Tmax+1]);
infected=zeros([box,box,Tmax+1]);

%define initial conditions
B(:,:,1)=B0;
p0=zeros([box,box]);
p0(X.^2+Y.^2<=Pstart^2)=P0;
size(p0)
P(:,:,1)=p0;

%%start dynamics
t=1;
Bmax=max(max(B(:,:,t)));
while(B(box-10,x(end),t)/Bmax>0.1 && t<=Tmax)
   t=t+1;
   %%perform diffusion
    %%create shifted matrices
    Pright=circshift(P(:,:,t-1),1,2);
    Pleft=circshift(P(:,:,t-1),-1,2);
    Pup=circshift(P(:,:,t-1),1,1);
    Pdown=circshift(P(:,:,t-1),-1,1);
    tphageold=sum(sum(P(:,:,t-1)));
    P(:,:,t-1)=P(:,:,t-1)-4*D*P(:,:,t-1)+D*(Pright+Pleft+Pup+Pdown);
    tphagenew=sum(sum(P(:,:,t-1)));
    if(abs(tphagenew-tphageold)>0.1)
        t
        tphageold
        tphagenew
        break
    end
   %local dynamics
   if(K<max(max(B(:,:,t-1))))
       K
       t
       max(max(B(:,:,t-1)))
       return
   end
   if(B(:,:,t-1)<K)
        B(:,:,t-1)=1.0234*B(:,:,t-1).*(1-1/K*B(:,:,t-1));
   end
   B(:,:,t)=B(:,:,t-1)-min(alpha*P(:,:,t-1).*B(:,:,t-1),B(:,:,t-1));
   infected(:,:,t)=infected(:,:,t-1)+min(alpha*P(:,:,t-1).*B(:,:,t-1),B(:,:,t-1));
   if(t>L+1)
        P(:,:,t)=P(:,:,t-1)-min(alpha*P(:,:,t-1).*(B(:,:,t-1)+I(:,:,t-1)),P(:,:,t-1))+beta*(infected(:,:,t-L)-infected(:,:,t-L-1));
        I(:,:,t)=I(:,:,t-1)+min(alpha*P(:,:,t-1).*B(:,:,t-1),B(:,:,t-1))-(infected(:,:,t-L)-infected(:,:,t-L-1));
   else
        P(:,:,t)=P(:,:,t-1)-min(alpha*P(:,:,t-1).*(B(:,:,t-1)+I(:,:,t-1)),P(:,:,t-1));
        I(:,:,t)=I(:,:,t-1)+min(alpha*P(:,:,t-1).*B(:,:,t-1),B(:,:,t-1));
   end
   
   if(min(min(P(:,:,t)))<-0.1 || min(min(I(:,:,t)))<-0.1 || min(min(B(:,:,t)))<-0.1)
       t
       min(min(P(:,:,t)))
       min(min(B(:,:,t)))
       min(min(I(:,:,t)))
       break
   end
   Bmax=max(max(B(:,:,t)));
end
T=t;
Bmax=max(max(max(B(:,:,:))));
Pmax=max(max(max(P(:,:,:))));
%%make movie
figure(1)
for i=1:10:T
    Bmax=max(max(B(:,:,i)));
    Pmax=max(max(P(:,:,i)));
    subplot(2,3,1)
    imagesc(P(:,:,i),[0,Pmax])
    axis square
    colorbar
    set(gca,'FontSize',20,'LineWidth',2)
    title('Free Phage')
    subplot(2,3,2)
    imagesc(I(:,:,i)+B(:,:,i),[0,Bmax])
    axis square
    colorbar
    set(gca,'FontSize',20,'LineWidth',2)
    title('Bacteria')
    subplot(2,3,3)
    imagesc(I(:,:,i),[0,Bmax])
    axis square
    colorbar
    set(gca,'FontSize',20,'LineWidth',2)
    title('Infected Bacteria')
    subplot(2,3,[4,5,6])
    plot((0:x(end)+1)*dx,P((x(end):end),x(end),i)/Pmax,'k','LineWidth',2)
    hold on
    plot((0:x(end)+1)*dx,(I((x(end):end),x(end),i)+B((x(end):end),x(end),i))/Bmax,'b','LineWidth',2)
    plot((0:x(end)+1)*dx,I((x(end):end),x(end),i)/Bmax,'r','LineWidth',2)
    ylim([0,1])
    hold off
    title(int2str(i))
    legend('P','B','I')
    xlabel('Position (um)')
    ylabel('Concentration')
    set(gca,'FontSize',20,'LineWidth',2)
    pause(.0003)
end

%%make figure of front speed
figure(2)
for i=1:size(B,1)/2
    for j=1:T
        f(i,j)=I(x(end)+i,x(end),j)+B(x(end)+i,x(end),j);
        if(abs(f(i,j))<0.1)
            f(i,j)=0;
        end
    end
end
t=(1:T);
p=zeros(size(t));
t0=T;
for j=1:size(f,2)
       Bmax=max(max(B(:,:,j)));
    Pmax=max(max(P(:,:,j)));
    xfront(j)=find(f(:,j),1);
    mid(j)=find(f(:,j)/Bmax>0.5,1);
    if(xfront(j)>1 && t0==T) 
        t0=j;
    end
    if(j>t0+2)
        a=polyfit(t(t0:j),mid(t0:j),1);
        width(j)=a(2);
        a=polyfit(t(t0:j),xfront(t0:j),1);
        p(j)=a(1);
        width(j)=width(j)-a(2);
    end
end
subplot(3,1,1)
plot(t,xfront*dx,'k','LineWidth',2)
set(gca,'FontSize',20,'LineWidth',2)
xlabel('Time (min)')
ylabel('Front Position (um)')
subplot(3,1,2)
v=p*dx*60;
plot(t,v,'r','LineWidth',2)
ylim([0,max(v)]);
set(gca,'FontSize',20,'LineWidth',2)
xlabel('Time (min)')
ylabel('Front Velocity (um/h)')
subplot(3,1,3)
plot(t,width*dx,'b','LineWidth',2)
grid on
set(gca,'FontSize',20,'LineWidth',2)
xlabel('Time (min)')
ylabel('Front Width (um)')
ylim([0,max(width*dx)]);
avv=mean(v(end-20:end));
avw=mean(width(end-20:end)*dx);



