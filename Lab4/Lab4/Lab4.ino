#define NO_LCD 
#include  <Sparki.h>; // include the sparki library 
static int angle=-30;
static int counter = 0;
static int arr[60];
void setup() { 
  sparki.clearLCD();
} 

void loop() { 
  sparki.servo(angle); 
  angle=angle+1; 
  if(angle>30){ 
    angle=-30; sparki.println(); 
  } 
  int cm = sparki.ping(); // measures the distance with Sparki's eyes 
  sparki.print(cm); 
  sparki.print(" ");
  sparki.updateLCD();
  arr[counter] = cm;
  if(counter == 59){
    int sum = 0;
    int i = 0;
    int minD = 2000;
    for(i = 0; i< 60; i++){
      if(arr[counter]<minD){
        minD = arr[counter];
      }
    }
    for(i = 0; i< 60; i++){
      if(arr[counter]<minD+3){
        sum = (sum + arr[i])/2;
      }
    }
    sparki.clearLCD();
    sparki.println();
    sparki.println();
    sparki.print(sum); 
    sparki.print(" ");
    sparki.println();
    sparki.println();
    sparki.updateLCD();
    delay(2000);
    counter = 0;
  }
  counter++;
} 
