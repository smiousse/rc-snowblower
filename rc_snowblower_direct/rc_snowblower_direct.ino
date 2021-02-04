#include "PWM.hpp"

#define PIN_MOTOR_RIGHT_FORWARD 13 // Relay 1
#define PIN_MOTOR_RIGHT_REVERSE 12 // Relay 2

#define PIN_MOTOR_LEFT_FORWARD 11 // Relay 3
#define PIN_MOTOR_LEFT_REVERSE 10 // Relay 4

#define PIN_UP_DOWN_FORWARD 7 // Relay 5
#define PIN_UP_DOWN_REVERSE 6 // Relay 6

#define PIN_SNOW_FALL_FORWARD 9 // Relay 7
#define PIN_SNOW_FALL_REVERSE 8 // Relay 8

#define PIN_CH_SNOW_FALL 4 
#define PIN_CH_FORWARD_REVERSE 2 
#define PIN_CH_LEFT_RIGHT 3 
#define PIN_CH_UP_DOWN 5 
#define PIN_CH_SPEED 6 

PWM chSnowFall(4); // for snow direction (CH2)
PWM chForwardReverse(2); // for forward / reverse joystick (CH3)
PWM chLeftRight(3); // for left / right joystick (CH1)
PWM chUpDown(5); // for up / down joystick (CH5)
PWM chSpeed(6); // for motor speed (CH6)

 
int chLeftRightValue;
int chForwardReverseValue;
int chUpDownValue;
int chSnowFallValue;
int chSpeedValue;

boolean driveMotorRuning = false;
boolean debug = true;
String driveMotorState = "STOP";
String upDownMotorState = "STOP";
String snowFallMotorState = "STOP";

void setup() {

  Serial.begin(9600); // Serial for debug

  // Setup receiver pins
  chSnowFall.begin(true);
  chForwardReverse.begin(true);
  chLeftRight.begin(true);
  chUpDown.begin(true);
  chSpeed.begin(true);

  // Setup motor pins
  pinMode(PIN_MOTOR_RIGHT_FORWARD, OUTPUT);
  pinMode(PIN_MOTOR_RIGHT_REVERSE, OUTPUT);
  pinMode(PIN_MOTOR_LEFT_FORWARD, OUTPUT);
  pinMode(PIN_MOTOR_LEFT_REVERSE, OUTPUT);
  
  //driveMotorStop();

  // Setup snowfall motor pins
  pinMode(PIN_SNOW_FALL_FORWARD, OUTPUT);
  pinMode(PIN_SNOW_FALL_REVERSE, OUTPUT);
  
  digitalWrite(PIN_SNOW_FALL_FORWARD,LOW);
  digitalWrite(PIN_SNOW_FALL_REVERSE,LOW);

  // Setup up/down motor pins
  pinMode(PIN_UP_DOWN_FORWARD, OUTPUT);
  pinMode(PIN_UP_DOWN_REVERSE, OUTPUT);
  
  digitalWrite(PIN_UP_DOWN_FORWARD,LOW);
  digitalWrite(PIN_UP_DOWN_REVERSE,LOW);

}

void loop() {

  chLeftRightValue = chLeftRight.getValue(); 
  chForwardReverseValue = chForwardReverse.getValue();
  chUpDownValue = chUpDown.getValue();
  chSpeedValue = chSpeed.getValue();
  chSnowFallValue = chSnowFall.getValue();

  //handleMotorDirection();
  //handleUpDown();
  //handleSnowFall();

  printDebug();
  delay(500);
   
}

void handleMotorDirection(){  
  if(chForwardReverseValue < 900){
    // lost communication do nothing
    Serial.println("LOST communication"); 
  } else { 
    driveMotorRuning = false;
    if(isInFRTopRange(chForwardReverseValue)){    
      driveMotorRuning = true;
      driveMotorForward();    
    } else if(isInFRBottomRange(chForwardReverseValue)){    
      driveMotorRuning = true;
      driveMotorReverse();    
    } else if(isInLRTopRange(chLeftRightValue)){    
      driveMotorRuning = true;
      driveMotorRight(); 
    } else if(isInLRBottomRange(chLeftRightValue)){    
      driveMotorRuning = true;   
      driveMotorLeft();    
    }
    if(!driveMotorRuning){    
      driveMotorStop();
    }
  }
}

void handleUpDown(){  
  //if(chUpDownValue > 1400 && chUpDownValue < 1500){
    // lost communication do nothing
  //} else {
    upDownMotorState = "STOP"; 
    if(chUpDownValue > 1800){ // switch facing down
      upDownMotorState = "REVERSE";
      digitalWrite(PIN_UP_DOWN_FORWARD,LOW);
      digitalWrite(PIN_UP_DOWN_REVERSE,HIGH);
    } else if(chUpDownValue < 1200 && chUpDownValue > 900){// switch facing up
      upDownMotorState = "FORWARD"; 
      digitalWrite(PIN_UP_DOWN_FORWARD,HIGH);
      digitalWrite(PIN_UP_DOWN_REVERSE,LOW);      
    } else {
      digitalWrite(PIN_UP_DOWN_FORWARD,LOW);
      digitalWrite(PIN_UP_DOWN_REVERSE,LOW);  
    }
  //}
}

void handleSnowFall(){
  snowFallMotorState = "STOP"; 
  if(chSnowFallValue > 1400 && chSnowFallValue < 1500){
    // lost communication do nothing
  } else {
    if(chSnowFallValue > 1500){
      snowFallMotorState = "FORWARD";
      digitalWrite(PIN_SNOW_FALL_FORWARD,HIGH);
      digitalWrite(PIN_SNOW_FALL_REVERSE,LOW);
    } else if(chSnowFallValue > 1100 && chSnowFallValue < 1200){
      snowFallMotorState = "REVERSE";
      digitalWrite(PIN_SNOW_FALL_FORWARD,LOW);
      digitalWrite(PIN_SNOW_FALL_REVERSE,HIGH);
    } else {
      digitalWrite(PIN_SNOW_FALL_FORWARD,LOW);
      digitalWrite(PIN_SNOW_FALL_REVERSE,LOW);  
    }
  }
}

void driveMotorStop(){  
  driveMotorState = "STOP";  
  digitalWrite(PIN_MOTOR_RIGHT_FORWARD,LOW);
  digitalWrite(PIN_MOTOR_RIGHT_REVERSE,LOW);
  digitalWrite(PIN_MOTOR_LEFT_FORWARD,LOW);
  digitalWrite(PIN_MOTOR_LEFT_REVERSE,LOW);
}

void driveMotorForward(){
  driveMotorState = "FORWARD";  
  digitalWrite(PIN_MOTOR_RIGHT_FORWARD,HIGH);
  digitalWrite(PIN_MOTOR_RIGHT_REVERSE,LOW);
  digitalWrite(PIN_MOTOR_LEFT_FORWARD,HIGH);
  digitalWrite(PIN_MOTOR_LEFT_REVERSE,LOW);
}

void driveMotorReverse(){
  driveMotorState = "REVERSE";  
  digitalWrite(PIN_MOTOR_RIGHT_FORWARD,LOW);
  digitalWrite(PIN_MOTOR_RIGHT_REVERSE,HIGH);
  digitalWrite(PIN_MOTOR_LEFT_FORWARD,LOW);
  digitalWrite(PIN_MOTOR_LEFT_REVERSE,HIGH);
}

void driveMotorRight(){
  driveMotorState = "RIGHT";
  digitalWrite(PIN_MOTOR_RIGHT_FORWARD,LOW);
  digitalWrite(PIN_MOTOR_RIGHT_REVERSE,HIGH);
  digitalWrite(PIN_MOTOR_LEFT_FORWARD,HIGH);
  digitalWrite(PIN_MOTOR_LEFT_REVERSE,LOW);   
}

void driveMotorLeft(){
  driveMotorState = "LEFT";
  digitalWrite(PIN_MOTOR_RIGHT_FORWARD,HIGH);
  digitalWrite(PIN_MOTOR_RIGHT_REVERSE,LOW);
  digitalWrite(PIN_MOTOR_LEFT_FORWARD,LOW);
  digitalWrite(PIN_MOTOR_LEFT_REVERSE,HIGH);  
}

void printDebug(){
  if(debug){
    Serial.print("LR = ");
    Serial.print(chLeftRightValue);
    Serial.print(", FR = ");
    Serial.print(chForwardReverseValue);
    Serial.print(", UD = ");
    Serial.print(chUpDownValue);
    Serial.print(", SF = ");
    Serial.print(chSnowFallValue);
    Serial.print(", SPEED = ");
    Serial.print(chSpeedValue);
    Serial.print(", driveMotorState = ");
    Serial.print(driveMotorState);
    Serial.print(", upDownMotorState = ");
    Serial.print(upDownMotorState);
    Serial.print(", snowFallMotorState = ");
    Serial.println(snowFallMotorState);    
  }
}

boolean isInFRTopRange(int chValue){
  return chValue > 1800 && chValue < 2000;
}

boolean isInFRBottomRange(int chValue){
  return chValue > 900 && chValue < 1050;
}

boolean isInLRTopRange(int chValue){
  return chValue > 1550 && chValue < 1700;
}

boolean isInLRBottomRange(int chValue){
  return chValue > 1100 && chValue < 1250;
}
