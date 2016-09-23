#include <sparki.h>
#include <math.h>
unsigned long time;
double speedForward;
double speedTurning;
double xi;
double yi;
double theta;
bool start;


void setup(){
  //Serial.begin(9600);
    sparki.clearLCD();
    speedForward = (.3/10.77)/10.0;
    speedTurning = (5*M_PI/24)/10.0;
    xi = 0;
    yi = 0;
    theta = 0.0;
    start = true;
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
    xi=0;
    yi=0;
    theta=0.0;
    start = false;
    sparki.beep(); 
  }
  else if(lineCenter < threshold && lineLeft < threshold && lineRight < threshold && !start && (xi <= .1 && xi >= -.1)&&(yi <= .1 && yi >= -.1))
  {
    xi=0;
    yi=0;
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

  
  
  // Integration

  
  // eat up remaining time
  while (millis()<time+100);
  theta = theta + thetadot;
  xi = xi + cos(theta)*xdot;
  yi = yi + sin(theta)*xdot;
}
