#include "MultiDirectionalMotor.h"

#define PIN_MOTOR_RIGHT_FORWARD 13 // Relay 1
#define PIN_MOTOR_RIGHT_REVERSE 12 // Relay 2

#define PIN_MOTOR_LEFT_FORWARD 11 // Relay 3
#define PIN_MOTOR_LEFT_REVERSE 10 // Relay 4

#define PIN_MOTOR_LEFT_SPEED 4
#define PIN_MOTOR_RIGHT_SPEED 5

#define PIN_UP_DOWN_FORWARD 7 // Relay 5
#define PIN_UP_DOWN_REVERSE 6 // Relay 6

#define PIN_SNOW_FALL_FORWARD 9 // Relay 7
#define PIN_SNOW_FALL_REVERSE 8 // Relay 8

#define PIN_CH_SNOW_FALL 4 
#define PIN_CH_FORWARD_REVERSE 2 
#define PIN_CH_LEFT_RIGHT 3 
#define PIN_CH_UP_DOWN 5 
#define PIN_CH_SPEED 6 

MultiDirectionalMotor snowBlowerDirection("snowBlowerDirection", PIN_MOTOR_LEFT_FORWARD, PIN_MOTOR_LEFT_REVERSE, PIN_MOTOR_RIGHT_FORWARD, PIN_MOTOR_RIGHT_REVERSE, PIN_MOTOR_RIGHT_SPEED, PIN_MOTOR_RIGHT_SPEED);

void setup() {

  Serial.begin(9600); // Serial for debug

  snowBlowerDirection.init();


}

void loop() {

  delay(100);
   
}

