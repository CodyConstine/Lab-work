#include <sparki.h>
#include <math.h>

double d;
double r;
unsigned long time;
double speedForward;
double speedTurning;
double xi;
double yi;
double theta;
bool start;


int percR, percL;

double xG , yG, thetaG;

double p , a , n;

double xDot, thetaDot;

double speedR, speedL;

double stepR, stepL;


void setup() {
  // put your setup code here, to run once:
  d = .08255;
  r = .0220;
  sparki.clearLCD();
  speedForward = (.3/10.77);
  speedTurning = (5*M_PI/24);
  xi = 0;
  yi = 0;
  theta = 0.0;
  start = true;

  xG = .5;
  yG = .5;
  thetaG = M_PI/4;

  p = sqrt(pow((xi-xG),2)+pow((yi-yG),2));//forward distance
  a = theta - atan((yi-yG)/(xi-xG));//rotation to goal
  n = thetaG - theta;//goal rotation

  double p1 = 1;
  double p2 = 1;
  double p3 = 0.001;

  xDot = p1*p;
  thetaDot = p2*a+p3*n;

  speedR = ((2*xDot/r)+(thetaDot*d/r))/2;
  speedL = ((2*xDot/r)-(thetaDot*d/r))/2;
  percR = (speedR/(speedTurning));//calculates percentage of max wheel speed
  percL = (speedL/(speedTurning));
  
}

void loop() {
  // put your main code here, to run repeatedly:
  /*double xdot = 0;
  double thetadot = 0;*/
  time = millis();

  sparki.motorRotate(MOTOR_LEFT, DIR_CCW, percL);
  sparki.motorRotate(MOTOR_RIGHT, DIR_CW, percR);
  //sparki.stepLeft(stepL);
  //sparki.stepRight(stepR);  
  sparki.clearLCD(); // wipe the screen

  sparki.print("sL: "); // show left line sensor on screen
  sparki.print(speedL);
  sparki.print(" pL: ");
  sparki.println(percL);

  sparki.print("sR: "); // show center line sensor on screen
  sparki.print(speedR);
  sparki.print(" pR: ");
  sparki.println(percR);

  sparki.print("theta Dot: "); // show center line sensor on screen
  sparki.println(thetaDot);


  while(time>millis()+100);
  theta = theta - thetaDot*.1;
  xi = xi + cos(theta)*xDot*.1;
  yi = yi + sin(theta)*xDot*.1;

  sparki.print("xi: "); // show left line sensor on screen
  sparki.println(xi);

  sparki.print("yi: "); // show center line sensor on screen
  sparki.println(yi);

  sparki.print("theta: "); // show center line sensor on screen
  sparki.println(theta);
  sparki.updateLCD();
}
