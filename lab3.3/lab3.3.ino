#include <sparki.h>
#include <math.h>
unsigned long time;
double speedForward;
double speedTurning;
double xi;
double yi;
double theta;
bool start;
short servo;
short grid[4][4];
short xPos;
short yPos;
struct position
{
  short x;
  short y;
};
short path[16];
int code;
double d;
double r;

int percR, percL;

double xG , yG, thetaG;

double p , a , n;

double xDot, thetaDot;

double speedR, speedL;


typedef struct position Position;
Position index[16];

int pointToIndex(int x, int y)
{
  x = x*10;
  y = y*10;
  return grid[x][y];
}
void indexAssign(){
  int i,ii;
  int counter = 0;
   for(i=0;i<5;i++)
    {
      for(ii=0;ii<5;ii++)
      {
        index[counter].x = i;
        index[counter].y = ii;
        counter++;
      }
    }
}
int getCords(int i)
{
  return index[i].x, index[i].y;
}

int getWeight(int s, int e)
{
  int xS, yS, xE, yE;
  xS, yS = getCords(s);
  xE, yE = getCords(e);
  if(grid[xS][yS] == 0 || grid[xE][yE] == 0)
  {
    return 99;
  }
  else if(abs(xS-xE) == 1 && abs(yS-yE) == 1)
  {
    return 1;
  }
  else
  {
    return 99;
  }
}


void dij(int n,int v,int cost[10][10],int dist[])
{
 int i,u,count,w,flag[10],min;
 for(i=1;i<=n;i++)
 {
  flag[i]=0,dist[i]=getWeight(v,i);
 }
 count=2;
 while(count<=n)
 {
  min=99;
  for(w=1;w<=n;w++)
  {
   if(dist[w]<min && !flag[w])
   {
    min=dist[w],u=w;
   }
  }
  flag[u]=1;
  count++;
  for(w=1;w<=n;w++)
  {
   if((dist[u]+getWeight(u,w)<dist[w]) && !flag[w])
   {
    dist[w]=dist[u]+getWeight(u,w);
    path[w]=u;
   }
  }
 }
}

int * pathReturn(int start, int source){
  int next = start;
  int r[16];
  int i = 0;
  while(next != source){
    r[i] = next;
    next = path[next];
    i++;
  }
  return r;
}

void inverseKin(int i){
    d = .08255;
    r = .0220;
    sparki.clearLCD();
    speedForward = (.3/10.77);
    speedTurning = (5*M_PI/24);
    xi = 0;
    yi = 0;
    theta = 0.0;
    start = true;

    xG = .2;
    yG = -.2;
    thetaG = M_PI/4;

    p = sqrt(pow((xi-xG),2)+pow((yi-yG),2));//forward distance
    a = theta - atan((yi-yG)/(xi-xG));//rotation to goal
    n = thetaG - theta;//goal rotation

    double p1 = .01;
    double p2 = .01;
    double p3 = 0.001;

    xDot = p1*p;
    thetaDot = p2*a+p3*n;

    speedR = ((2*xDot/r)+(thetaDot*d/r))/2;
    speedL = ((2*xDot/r)-(thetaDot*d/r))/2;
    percR = 100* (speedR/(speedTurning*2));//calculates percentage of max wheel speed
    percL = 100* (speedL/(speedTurning*2));
}


void setup(){
  //Serial.begin(9600);
    sparki.clearLCD();
    speedForward = (.3/10.77)/10.0;
    speedTurning = (5*M_PI/24)/10.0;
    xi = 0;
    yi = 0;
    theta = 0.0;
    start = true;
    servo = 0;
    sparki.servo(0);
    int i = 0;
    int ii = 0;
    for(i=0;i<5;i++)
    {
      for(ii=0;ii<5;ii++)
      {
        grid[i][ii]=1;
      }
    }
    sparki.servo(-45);
    xPos = 0;
    yPos = 0;
    code = 0;
}




void loop(){
  double xdot = 0;
  double thetadot = 0;
  time = millis();
  switch(code) {
      case 0: {

      }
      break;
      default: {
          sparki.moveStop();
      }
  }
}
