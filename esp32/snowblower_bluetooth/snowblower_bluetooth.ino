#include "MdMotorWithController.h"
#include <Ps3Controller.h>
#include <analogWrite.h>

const int ONBOARD_LED = 2;

// Robot motor pins
#define ML_Ctrl 19  //define direction control pin of left motor controller pin 13
#define ML_PWM 16   //define PWM control pin of left motor controller pin 11
#define MR_Ctrl 18  //define direction control pin of right motor controller pin 12  
#define MR_PWM 17    //define PWM control pin of right motor controller pin 3 

#define PIN_UP_DOWN_FORWARD 6 // Relay 5
#define PIN_UP_DOWN_REVERSE 7 // Relay 6

#define PIN_SNOW_FALL_FORWARD 8 // Relay 7
#define PIN_SNOW_FALL_REVERSE 9 // Relay 8


char bluetooth_val = 'S'; //save the value of Bluetooth reception
int player = 0;

MdMotorWithController snowblower("robot", ML_Ctrl, MR_Ctrl, ML_PWM, MR_PWM, 0);
//BdMotorWithRelay upDown("upDown", PIN_UP_DOWN_FORWARD, PIN_UP_DOWN_REVERSE, 0);
//BdMotorWithRelay snowfall("snowfall", PIN_SNOW_FALL_FORWARD, PIN_SNOW_FALL_REVERSE, 0);

void setup() {
  Serial.begin(115200); // Serial for debug
  snowblower.init();
  //upDown.init();
  //snowfall.init();
  Ps3.attach(notify);
  Ps3.attachOnConnect(onConnect);
  Ps3.begin("1a:2b:3c:01:01:01");
  Serial.println("Ready !");
  pinMode(ONBOARD_LED, OUTPUT); 
  
}

void loop() {
  
  if(!Ps3.isConnected())
    return;

  if(player == 0){
    //-------------------- Player LEDs -------------------
    Serial.print("Setting LEDs to player "); 
    Serial.println(player, DEC);
    Ps3.setPlayer(player);

    player += 1;
  }

  delay(2000);

}


void onConnect(){
    Serial.println("Connected.");
    analogWrite(ONBOARD_LED, 255);
    Ps3.setPlayer(1);    
}

void notify(){

  if( Ps3.event.button_down.cross ){
      bluetooth_val = 'H';
  } else if( Ps3.event.button_up.cross ){
      bluetooth_val = 'O';
  }

  if( Ps3.event.button_down.square ){
      bluetooth_val = 'D';
  } else if( Ps3.event.button_up.square ){
      bluetooth_val = 'T';
  }

  if( Ps3.event.button_down.triangle ){
      bluetooth_val = 'G';
  } else if( Ps3.event.button_up.triangle ){
      bluetooth_val = 'O';
  }

  if( Ps3.event.button_down.circle ){
      bluetooth_val = 'Z';
  } else if( Ps3.event.button_up.circle ){
      bluetooth_val = 'T';
  }
  
  if( Ps3.event.button_down.up ){
      bluetooth_val = 'F';
  } else if( Ps3.event.button_up.up ){
      bluetooth_val = 'S';
  }
  
  if( Ps3.event.button_down.right ){
      bluetooth_val = 'R';
  }
  
  if( Ps3.event.button_down.down ){
      bluetooth_val = 'B';
  } else if( Ps3.event.button_up.down ){
      bluetooth_val = 'S';
  }
  
  if( Ps3.event.button_down.left ){
      bluetooth_val = 'L';
  }

  if( Ps3.event.button_down.l1 ){
      bluetooth_val = 'Y';
  }

  if( Ps3.event.button_down.r1 ){
      bluetooth_val = 'M';
  }

  if( Ps3.event.button_down.l2 ){
      bluetooth_val = 'P';
  }

  if( Ps3.event.button_down.r2 ){
      bluetooth_val = 'W';
  }

  if( Ps3.event.button_down.select ){
      bluetooth_val = 'I';
  }

  if( Ps3.event.button_down.start ){
      bluetooth_val = 'U';
  }
  
  if( Ps3.event.button_down.ps ){
      bluetooth_val = 'V';
  }

  if(bluetooth_val != ' '){
    Serial.println(bluetooth_val);
  }
  

  switch (bluetooth_val){
   case 'F': // snowblower forward
      snowblower.forward();
      Serial.println("Snowblower -> Forward");
      break;
   case 'B': // snowblower backward
      snowblower.reverse();
      Serial.println("Snowblower -> Reverse");
      break;
   case 'L': // snowblower turn left
      snowblower.fullLeft();
      Serial.println("Snowblower -> Turn left");
      break;
   case 'R': // snowblower turn right
      snowblower.fullRight();  
      Serial.println("Snowblower -> Turn right");
      break;  
   case 'M': // Snowblower forward and right
      snowblower.forwardRight();
      Serial.println("Snowblower -> Forward and right");
      break;
   case 'Y': // Snowblower forward and left
      snowblower.forwardLeft();
      Serial.println("Snowblower -> Forward and left");
      break;
   case 'W': // Snowblower reverse and right
      snowblower.reverseRight();
      Serial.println("Snowblower -> Reverse and right");
      break;
   case 'P': // Snowblower reverse and left
      snowblower.reverseLeft();
      Serial.println("Snowblower -> Reverse and left");
      break;      
   case 'S': // snowblower stop
      snowblower.stop();
      Serial.println("Snowblower -> STOP");
      break;
   case 'I': 
      snowblower.increaseSpeed();
      Serial.println("Snowblower -> Increase Speed");
      break;
   case 'U': 
      snowblower.decreaseSpeed();
      Serial.println("Snowblower -> Decrease Speed");
      break;
   case 'V': 
      snowblower.resetSpeed();
      Serial.println("Snowblower -> Reset Speed");
      break;
   case '1': 
      //snowblower.setSpeed(30);  
      break;
   case '2': 
      //snowblower.setSpeed(50); 
      break;
   case '3': 
      //snowblower.setSpeed(60); 
      break;
   case '4': 
      //snowblower.setSpeed(80); 
      break;
   case '5': 
      //snowblower.setSpeed(100);  
      break;
   case '6': 
      //snowblower.setSpeed(120);  
      break;
   case '7':
      //snowblower.setSpeed(140);  
      break;
   case '8': 
      //snowblower.setSpeed(150); 
      break;
   case '9': 
      //snowblower.setSpeed(160); 
      break;
   case 'G': // Snowblower up  
      //upDown.forward();
      Serial.println("Snowblower -> UP ");
      break;
   case 'H': // Snowblower down  
      //upDown.reverse();
      Serial.println("Snowblower -> DOWN");
      break;
   case 'O': // Snowblower UpDown stop
      //upDown.stop();
      Serial.println("Snowblower -> UpDown STOP");
      break;
   case 'D': // Snowfall left
      //snowfall.forward();
      Serial.println("Snowfall -> LEFT");
      break;
   case 'Z': // Snowfall right      
      //snowfall.reverse();
      Serial.println("Snowfall -> RIGHT");
      break;
   case 'T': // Snowfall stop
      //snowfall.stop();
      Serial.println("Snowfall -> STOP");
      break;
  }   
  bluetooth_val = ' ';
  
}
