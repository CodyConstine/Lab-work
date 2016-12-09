#include <sparki.h>
int code;
int beerCount;


void setup() {
  // put your setup code here, to run once:
  sparki.clearLCD();
  code = 7;
  beerCount = 1;
  sparki.servo(45);
  sparki.gripperOpen();
}

// /------^-----
// |            |
// | 69  70  71 |
// | 68  64  67 |
// |  7  21   9 |
// | 22  25  13 |
// | 12  24  94 |
// |  8  28  90 |
// | 66  82  74 |
// ____________/

void loop() {
  // put your main code here, to run repeatedly:
  int remote = sparki.readIR();

  if(remote == 12){
    beerCount = beerCount + 1;
  }
  else if(remote == 24){
    beerCount = beerCount + 2;
  }
  else if(remote == 94){
    beerCount = beerCount + 3;
  }
  else if(remote == 8){
    beerCount = beerCount + 4;
  }
  else if(remote == 28){
    beerCount = beerCount + 5;
  }
  else if(remote == 90){
    beerCount = beerCount + 6;
  }
  else if(remote == 66){
    beerCount = beerCount + 7;
  }
  else if(remote == 82){
    beerCount = beerCount + 8;
  }
  else if(remote == 74){
    beerCount = beerCount + 9;
  }

  sparki.clearLCD();
  sparki.print("Beer Count = ");
  sparki.println(beerCount);
  sparki.print("Code = ");
  sparki.println(code);
  switch(code){
    case 0: {
      //open fridge
      sparki.gripperStop();
      sparki.RGB(RGB_GREEN);
      sparki.servo(-20);
      if(sparki.ping() < 4 && sparki.ping()> 0){
        sparki.moveLeft(25);
        sparki.RGB(RGB_YELLOW);
        sparki.gripperStop();
        code = 1;
      }
      else {
        sparki.moveForward();
      }

    }
    break;
    case 1: {
      //grab beer
      //sparki.beep();
      sparki.RGB(RGB_RED);
      sparki.moveBackward(5);
      //sparki.moveRight(10);
      sparki.moveForward(18);
      //sparki.moveBackward(3);
      sparki.moveRight(115);
      code = 2;
    }
    break;
    case 2: {
      
      sparki.servo(0);
      //delay(2000);
      sparki.gripperStop();
      //close fridge
      sparki.moveForward();
      if(sparki.ping() < 6 && sparki.ping() > 0){
        sparki.moveForward(5);
        sparki.gripperClose();
        delay(3000);
        sparki.moveBackward();
        /*sparki.moveLeft(200);
        sparki.moveBackward(2);
        sparki.moveLeft(40);*/
        sparki.servo(-90);
        code = 3;
      }
      //code = 3;
    }
    break;
    case 3 : {
      sparki.print("Distance = ");
      sparki.println(sparki.ping());
      sparki.gripperStop();
      if(sparki.ping() > 22 || sparki.ping() < 0){
        sparki.moveBackward(8);
        code = 4;
      }
      //sparki.moveStop();
    }
    break;
    case 4: {
      sparki.RGB(RGB_YELLOW);
      sparki.moveLeft(130);
      sparki.moveForward(7);
      sparki.moveRight(130);
      sparki.moveForward(25);
      sparki.moveLeft(40);
      code = 5;
    }
    break;
    case 5: {
      //drop beer
      
      sparki.moveBackward(5);
      sparki.moveRight(120);
      sparki.moveForward(50);
      /*sparki.gripperOpen();
      sparki.moveBackward(5);
      sparki.gripperStop();
      sparki.moveLeft(180);
      beerCount = beerCount - 1;*/
      code = 6;
    }
    break;
    case 6: {
      sparki.gripperOpen();
      delay(1000);
      sparki.gripperStop();
      code = 7;
    }
    break;
    case 7: {
      //sparki.gripperOpen();
      //delay(8000);
      //wait till command to move
      sparki.moveForward();
      int dist = sparki.ping();
      if(dist< 10 && dist > 0){
        if(beerCount > 0){
          sparki.moveStop();
          code = 0;
        }
        else {
          code = 8;
        }
      }

    }
    break;
    case 8: {
      sparki.moveStop();
      if(beerCount > 0){
          code = 6;
      }
    }
    break;
  }
  
  sparki.updateLCD();
}
