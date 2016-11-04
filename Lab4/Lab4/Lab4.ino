#define NO_LCD 
#include  <Sparki.h>; // include the sparki library 
static int angle=-15;
static int counter = 0;
static int code = 0;
void setup() { 
  sparki.clearLCD();
} 

void loop() { 
  switch(code){
    case 0: {
      sparki.servo(angle); 
      angle=angle+1; 
      if(angle>30){ 
        angle=-30; sparki.println(); 
      } 
      int cm = sparki.ping(); // measures the distance with Sparki's eyes 
      sparki.print(cm); 
      sparki.print(" ");
      sparki.updateLCD();
      if(counter == 29){
        code = 1;
      }
      counter ++;
    }
    case 1: {
      sparki.moveStop();
    }
  }
} 
