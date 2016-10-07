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
}




void loop(){
  double xdot = 0;
  double thetadot = 0;
  time = millis();
  //prints time since program started
  // wait a second so as not to send massive amounts of data
  //delay(1000);
  int threshold = 700;

  int lineLeft   = sparki.lineLeft();   // measure the left IR sensor
  int lineCenter = sparki.lineCenter(); // measure the center IR sensor
  int lineRight  = sparki.lineRight();  // measure the right IR sensor
  sparki.clearLCD(); // wipe the screen

  sparki.print("Distance X: "); // show left line sensor on screen
  sparki.println(xi);

  sparki.print("Distance Y: "); // show center line sensor on screen
  sparki.println(yi);

  sparki.print("Radians: "); // show right line sensor on screen
  sparki.println(theta);

  sparki.updateLCD(); // display all of the information written to the screen

  if(lineCenter < threshold && lineLeft < threshold && lineRight < threshold && start)
  {
    xi=30;
    yi=5;
    theta=0.0;
    start = false;
    sparki.beep(); 
  }
  else if(lineCenter < threshold && lineLeft < threshold && lineRight < threshold && !start && (xi <= .1 && xi >= -.1)&&(yi <= .1 && yi >= -.1))
  {
    xi=30;
    yi=5;
    theta=0.0;
    start = false; 
    sparki.beep();
  }
  else if (lineCenter < threshold)
  {
    sparki.moveForward(); // move forward
    xdot = speedForward; thetadot = 0;
  }  
  else if ( lineLeft < threshold ) // if line is below left line sensor
  {
    sparki.moveLeft(); // turn left
    xdot = 0; thetadot = speedTurning;
  }

  else if ( lineRight < threshold ) // if line is below right line sensor
  {  
    sparki.moveRight(); // turn right
    xdot = 0; thetadot = -speedTurning;
  }
  int ping = sparki.ping();
  if(ping < 15){
    int x = ping*cos(M_PI/4);
    int y = ping*sin(M_PI/4);
    int xPos = xi+x*cos(theta);
    int yPos = yi+y*sin(theta);
    x = xPos*10;
    y = yPos*10;
    grid[x][y] = 0;
  }
  // Integration

  if(millis()>time+100)
  {
    sparki.moveStop();
  }
  // eat up remaining time
  while (millis()<time+100);
  theta = theta + thetadot;
  xi = xi + cos(theta)*xdot;
  yi = yi + sin(theta)*xdot;
}
