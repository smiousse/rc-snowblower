#include "BdMotorWithRelay.h"
#include "MdMotorWithController.h"

// Robot motor pins
#define ML_Ctrl 13  //define direction control pin of left motor
#define ML_PWM 11   //define PWM control pin of left motor
#define MR_Ctrl 12  //define direction control pin of right motor
#define MR_PWM 10    //define PWM control pin of right motor

#define PIN_UP_DOWN_FORWARD 6 // Relay 5
#define PIN_UP_DOWN_REVERSE 7 // Relay 6

#define PIN_SNOW_FALL_FORWARD 8 // Relay 7
#define PIN_SNOW_FALL_REVERSE 9 // Relay 8


char bluetooth_val = 'S'; //save the value of Bluetooth reception

MdMotorWithController snowblower("robot", ML_Ctrl, MR_Ctrl, ML_PWM, MR_PWM, 2);
BdMotorWithRelay upDown("upDown", PIN_UP_DOWN_FORWARD, PIN_UP_DOWN_REVERSE, 0);
BdMotorWithRelay snowfall("snowfall", PIN_SNOW_FALL_FORWARD, PIN_SNOW_FALL_REVERSE, 0);


void setup() {
  Serial.begin(9600); // Serial for debug
  snowblower.init();
  upDown.init();
  snowfall.init();
}

void loop() {

  if (Serial.available()){
    bluetooth_val = Serial.read();
    Serial.println(bluetooth_val);
  }

  switch (bluetooth_val){
   case 'F': // snowblower forward
      snowblower.forward();
      break;
   case 'B': // snowblower backward
      snowblower.reverse();
      break;
   case 'L': // snowblower turn left
      snowblower.fullLeft();
      break;
   case 'R': // snowblower turn right
      snowblower.fullRight();  
      break;  
   case 'M': // Snowblower forward and right
      snowblower.forwardRight();
      break;
   case 'Y': // Snowblower forward and left
      snowblower.forwardLeft();
      break;
   case 'W': // Snowblower reverse and right
      snowblower.reverseRight();
      break;
   case 'P': // Snowblower reverse and left
      snowblower.reverseLeft();
      break;      
   case 'S': // snowblower stop
      snowblower.stop();
      break;
   case '1': 
      snowblower.setSpeed(30);  
      bluetooth_val = ' ';
      break;
   case '2': 
      snowblower.setSpeed(50); 
      bluetooth_val = ' '; 
      break;
   case '3': 
      snowblower.setSpeed(60); 
      bluetooth_val = ' ';  
      break;
   case '4': 
      snowblower.setSpeed(80);
      bluetooth_val = ' ';   
      break;
   case '5': 
      snowblower.setSpeed(100);  
      bluetooth_val = ' '; 
      break;
   case '6': 
      snowblower.setSpeed(120); 
      bluetooth_val = ' ';  
      break;
   case '7':
      snowblower.setSpeed(140);  
      bluetooth_val = ' '; 
      break;
   case '8': 
      snowblower.setSpeed(150); 
      bluetooth_val = ' ';  
      break;
   case '9': 
      snowblower.setSpeed(160);
      bluetooth_val = ' ';   
      break;
   case 'G': // Snowblower up  
      upDown.forward();
      break;
   case 'H': // Snowblower down  
      upDown.reverse();
      break;
   case 'O': // Snowblower UpDown stop
      upDown.stop();
      break;
   case 'D': // Snowfall left
      snowfall.forward();
      break;
   case 'Z': // Snowfall right      
      snowfall.reverse();
      break;
   case 'T': // Snowfall stop
      snowfall.stop();
      break;
  } 
}
