#include "MdMotorWithRelay.h"
#include "BdMotorWithRelay.h"
#include "MdMotorWithController.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Robot motor pins
#define ML_Ctrl 13  //define direction control pin of left motor
#define ML_PWM 11   //define PWM control pin of left motor
#define MR_Ctrl 12  //define direction control pin of right motor
#define MR_PWM 3    //define PWM control pin of right motor

// Snowblower motors pins
#define PIN_MOTOR_RIGHT_FORWARD 22 // Relay 1
#define PIN_MOTOR_RIGHT_REVERSE 23 // Relay 2

#define PIN_MOTOR_LEFT_FORWARD 24 // Relay 3
#define PIN_MOTOR_LEFT_REVERSE 25 // Relay 4

#define PIN_MOTOR_LEFT_SPEED 44
#define PIN_MOTOR_RIGHT_SPEED 45

#define PIN_MOTOR_LEFT_ENABLE 30
#define PIN_MOTOR_RIGHT_ENABLE 31

#define PIN_UP_DOWN_FORWARD 26 // Relay 5
#define PIN_UP_DOWN_REVERSE 27 // Relay 6

#define PIN_SNOW_FALL_FORWARD 28 // Relay 7
#define PIN_SNOW_FALL_REVERSE 29 // Relay 8

// Rf antena pins
#define PIN_RF_CE 7
#define PIN_RF_CSN 8

const uint64_t pipes[] = { 0x65646f4e31 };
char bluetooth_val; //save the value of Bluetooth reception

MdMotorWithController robot("robot", ML_Ctrl, MR_Ctrl, ML_PWM, MR_PWM, 2);
MdMotorWithRelay snowblower("snowblower", PIN_MOTOR_LEFT_FORWARD, PIN_MOTOR_LEFT_REVERSE, PIN_MOTOR_RIGHT_FORWARD, PIN_MOTOR_RIGHT_REVERSE, PIN_MOTOR_RIGHT_SPEED, PIN_MOTOR_LEFT_SPEED, 2);
BdMotorWithRelay upDown("upDown", PIN_UP_DOWN_FORWARD, PIN_UP_DOWN_REVERSE, 0);
BdMotorWithRelay snowfall("snowfall", PIN_SNOW_FALL_FORWARD, PIN_SNOW_FALL_REVERSE, 0);

RF24 radio(PIN_RF_CE, PIN_RF_CSN); // CE, CSN

void setup() {

  Serial.begin(9600); // Serial for debug

  // The relay control 2 cheap motor controller that need to be enabled
  // so I out 5v to enable it
  pinMode(PIN_MOTOR_LEFT_ENABLE, OUTPUT);
  pinMode(PIN_MOTOR_RIGHT_ENABLE, OUTPUT);
  digitalWrite(PIN_MOTOR_LEFT_ENABLE,HIGH);
  digitalWrite(PIN_MOTOR_RIGHT_ENABLE,HIGH);

  robot.init();
  snowblower.init();
  upDown.init();
  snowfall.init();

  // RF receiver part
  radio.begin();
  radio.openReadingPipe(0, pipes[0]);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();

  Serial.println("Starting read on 0x65646f4e31");

}

void loop() {
  
/*  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    bluetooth_val = text[0];
  }*/ 
  
  if (Serial.available()){
    bluetooth_val = Serial.read();
    Serial.println(bluetooth_val);
  }

  switch (bluetooth_val){
   case 'F': // snowblower forward
      robot.forward();
      snowblower.forward();
      break;
   case 'B': // snowblower backward
      robot.reverse();
      snowblower.reverse();
      break;
   case 'L': // snowblower turn left
      robot.fullLeft();
      snowblower.fullLeft();
      break;
   case 'R': // snowblower turn right
      robot.fullRight();  
      snowblower.fullRight();  
      break;  
   case 'M': // Snowblower forward and right
      robot.forwardRight();
      snowblower.forwardRight();
      break;
   case 'N': // Snowblower forward and left
      robot.forwardLeft();
      snowblower.forwardLeft();
   case 'O': // Snowblower reverse and right
      robot.reverseRight();
      snowblower.reverseRight();
      break;
   case 'P': // Snowblower reverse and left
      robot.reverseLeft();
      snowblower.reverseLeft();
      break;      
   case 'S': // snowblower stop
      robot.stop();
      snowblower.stop();
      break;
   case '1': 
      robot.setSpeed(10);  
      bluetooth_val = '0';
      break;
   case '2': 
      robot.setSpeed(40); 
      bluetooth_val = '0'; 
      break;
   case '3': 
      robot.setSpeed(70); 
      bluetooth_val = '0';  
      break;
   case '4': 
      robot.setSpeed(100);
      bluetooth_val = '0';   
      break;
   case '5': 
      robot.setSpeed(130);  
      bluetooth_val = '0'; 
      break;
   case '6': 
      robot.setSpeed(160); 
      bluetooth_val = '0';  
      break;
   case '7':
      robot.setSpeed(190);  
      bluetooth_val = '0'; 
      break;
   case '8': 
      robot.setSpeed(220); 
      bluetooth_val = '0';  
      break;
   case '9': 
      robot.setSpeed(248);
      bluetooth_val = '0';   
      break;
   case 'G': // Snowblower up  
      upDown.forward();
      break;
   case 'H': // Snowblower down  
      upDown.reverse();
      break;
   case 'D': // Snowfall left
      snowfall.forward();
      break;
   case 'C': // Snowfall right      
      snowfall.reverse();
      break;
   case 'T': // Snowfall stop
      snowfall.stop();
      break;
   case 'V': // Snowblower UpDown stop
      upDown.stop();
      break;
  }
  bluetooth_val = ' ';   
}
