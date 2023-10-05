//Problem statement: Write a program to implement tower of Hanoi game using DDA line drawing algorithm.

/*Theory: 
DDA stands for Digital Differential Analyzer. It is an incremental method of scan conversion of line. In this method calculation is performed at each step but by using results of previous steps.
Case1: When |M|<1 then (assume that x1<x2)
              x= x1,y=y1 set ∆x=1
              yi+1=y1+m,     x=x+1
              Until x = x2</x
Case2: When |M|<1 then (assume that y1<y2)
              x= x1,y=y1 set ∆y=1
              xi+1=1/m,     y=y+1
              Until y → y2</y 
  */




#include<stdio.h>
#include<graphics.h>
#include<dos.h>
#include<math.h>

int tower[3][10];// the three towers' disks as stack
int top[3];//top of the three stacks
int from,to;//moving 'from' tower number 'to' tower number
int diskInAir;//number of disk moved (1 to n)
int l,b,u;

//dda function//
void dda(float x1,float y1,float x2,float y2){
float x,y,dx,dy,step,i;
dx=abs(x2-x1);
dy=abs(y2-y1);
 if(dx>=dy)
step=dx;
else
step=dy;
 dx=dx/step;
dy=dy/step;
 x=x1;
 y=y1;
 i=1;
while(i<=step)
{
putpixel(x,y,15);
x=x+dx;
y=y+dy;
i=i+1;
}
}
//dda function

void push(int to, int diskno)
//putting disk on tower
{
tower[to-1][++top[to-1]]=diskno;
}

int pop(int from)
//take topmost disk from tower
{
return(tower[from-1][top[from-1]--]);
}

void drawStill()
{
int j,i,disk;
cleardevice();
for(j=1;j<=3;j++)
 {
 //draw tower
 setfillstyle(CLOSE_DOT_FILL,WHITE);
dda(j*l,u,j*l,b);
dda(j*l+2,u,j*l+2,b);
dda(j*l,u,j*l,b);
// bar(j*l,u,j*l+5,b);
 //draw all disks on tower
 for(i=0;i<=top[j-1];i++)
  {
  disk=tower[j-1][i];
  setfillstyle(SOLID_FILL,1+disk);

  bar(j*l-15-disk*5,b-(i+1)*10,j*l+5+15+disk*5,b-i*10);
  }
 }
}

void animator()
//to show the movement of disk
{
int x,y,dif,sign;
diskInAir=pop(from);
x=from*l;
y=b-(top[from-1]+1)*10;
//taking disk upward from the tower
for(;y>u-20;y-=15)
 {
 drawStill();
 setfillstyle(SOLID_FILL,1+diskInAir);
 bar(x-15-diskInAir*5,y-10,x+5+15+diskInAir*5,y);
 delay(100);
 }
y=u-20;
dif=to*l-x;
sign=dif/abs(dif);
//moving disk towards a target tower
for(;abs(x-to*l)>25;x+=sign*15)
 {
 drawStill();
 setfillstyle(SOLID_FILL,1+diskInAir);
 bar(x-15-diskInAir*5,y-10,x+5+15+diskInAir*5,y);
 delay(100);
 }
x=to*l;
//placing disk on a target tower
for(;y<b-(top[to-1]+1)*10;y+=15)
 {
 drawStill();
 setfillstyle(SOLID_FILL,1+diskInAir);
 bar(x-15-diskInAir*5,y-10,x+5+15+diskInAir*5,y);
 delay(100);
 }
push(to,diskInAir);
drawStill();
}

void moveTopN(int n, int a, int b, int c)
//Move top n disk from tower 'a' to tower 'c'
//tower 'b' used for swapping
{
if(n>=1)
 {
 moveTopN(n-1,a,c,b);
 drawStill();
 delay(1000);
 from=a;
 to=c;
 //animating the move
 animator();
 moveTopN(n-1,b,a,c);
 }
}

int main()
{
int i,gd=DETECT,gm,n;
printf("Enter number of disks");
scanf("%d",&n);
initgraph(&gd,&gm,"C:\\TURBOC3\\BGI\\");
//setting all tower empty
for(i=0;i<3;i++)
 {
 top[i]=-1;
 }
//putting all disks on tower 'a'
for(i=n;i>0;i--)
 {
 push(1,i);
 }
l=getmaxx()/4;
b=getmaxy()-50;
u=getmaxy()/3+100;
//start solving
moveTopN(n,1,2,3);
delay(4000);
getch();
}
