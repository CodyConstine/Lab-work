#include <sparki.h>
int code;
int beerCount;


void setup() {
  // put your setup code here, to run once:
  sparki.clearLCD();
  code = 6;
  beerCount = 1;
  sparki.servo(45);
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
  sparki.updateLCD();
  switch(code){
    case 0: {
      //open fridge
      sparki.RGB(RGB_GREEN);
      sparki.servo(-10);
      if(sparki.ping() < 4 && sparki.ping()> 0){
        sparki.moveLeft(25);
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
      sparki.moveRight(15);
      sparki.moveForward(10);
      sparki.moveRight(90);
      code = 2;
    }
    break;
    case 2: {
      //close fridge
      sparki.moveStop();
      code = 3;
    }
    break;
    case 3: {
      sparki.moveForward(40);
      sparki.moveRight(90);
      sparki.moveForward(40);
      code = 4;
    }
    break;
    case 4: {
      //drop beer
      sparki.gripperOpen();
      sparki.moveBackward(5);
      sparki.moveLeft(180);
      beerCount = beerCount - 1;
      code = 5;
    }
    break;
    case 5: {
      sparki.moveForward(35);
      sparki.moveLeft(90);
      sparki.moveForward(40);
      code = 6;
    }
    break;
    case 6: {
      //wait till command to move
      sparki.moveForward();
      int dist = sparki.ping();
      if(dist< 10 && dist > 0){
        if(beerCount > 0){
          sparki.moveStop();
          code = 0;
        }
        else {
          code = 7;
        }
      }

    }
    break;
    case 7: {
      sparki.moveStop();
      if(beerCount > 0){
          code = 6;
      }
    }
    break;
  }
}
