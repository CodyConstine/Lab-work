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


double xG , yG, thetaG;

double p , a , n;

double xDot, thetaDot;

double speedR, speedL;


void setup() {
  // put your setup code here, to run once:
  d = .08255;
  r = .026;
  sparki.clearLCD();
  speedForward = (.3/10.77)/10.0;
  speedTurning = (5*M_PI/24)/10.0;
  xi = 0;
  yi = 0;
  theta = 0.0;
  start = true;

  xG = 1;
  yG = 1;
  thetaG = M_PI/4;

  p = sqrt(pow((xi-xG),2)+pow((yi-yG),2));
  a = theta - atan((yi-yG)/(xi-xG));
  n = thetaG - theta;

  double p1 = 0.1;
  double p2 = 1;
  double p3 = 0.001;

  xDot = p1*p;
  thetaDot = p2*a+p3*n;

  speedR = ((2*xDot/r)+(thetaDot*d/r))/2;
  speedL = ((2*xDot/r)-(thetaDot*d/r))/2;
}

void loop() {
  // put your main code here, to run repeatedly:
  /*double xdot = 0;
  double thetadot = 0;*/
  time = millis();

  sparki.motorRotate(MOTOR_LEFT, DIR_CCW, speedL);
  sparki.motorRotate(MOTOR_RIGHT, DIR_CW, speedR);  

  sparki.clearLCD(); // wipe the screen

  sparki.print("speed left: "); // show left line sensor on screen
  sparki.println(speedL);

  sparki.print("speed Right: "); // show center line sensor on screen
  sparki.println(speedR);

  sparki.print("theta: "); // show center line sensor on screen
  sparki.println(thetaDot);

  sparki.updateLCD();
}
