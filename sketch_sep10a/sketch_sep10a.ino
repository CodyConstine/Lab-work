#include <sparki.h>
unsigned long time;
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  sparki.clearLCD();
  time = millis();
  sparki.moveForward(30);
  sparki.println(millis()-time);
  sparki.updateLCD();
}
