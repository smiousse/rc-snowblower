/*
 RC PulseIn Serial Read out
 By: Nick Poole
 SparkFun Electronics
 Date: 5
 License: CC-BY SA 3.0 - Creative commons share-alike 3.0
 use this code however you'd like, just keep this license and
 attribute. Let me know if you make hugely, awesome, great changes.
 */
 
int chLeftRight; // Here's where we'll keep our channel values
int chForwardReverse;
int chUpDown;
int chSnowFall;

boolean driveMotorRuning = false;
boolean debug = true;
String driveMotorState = "STOP";
String upDownMotorState = "STOP";
String snowFallMotorState = "STOP";

#define PIN_MOTOR_RIGHT_FORWARD 13 // Relay 1
#define PIN_MOTOR_RIGHT_REVERSE 12 // Relay 2

#define PIN_MOTOR_LEFT_FORWARD 11 // Relay 3
#define PIN_MOTOR_LEFT_REVERSE 10 // Relay 4

#define PIN_UP_DOWN_FORWARD 7 // Relay 5
#define PIN_UP_DOWN_REVERSE 6 // Relay 6

#define PIN_SNOW_FALL_FORWARD 9 // Relay 7
#define PIN_SNOW_FALL_REVERSE 8 // Relay 8

#define PIN_CH_SNOW_FALL 4 // for snow direction (CH2)
#define PIN_CH_FORWARD_REVERSE 2 // for forward / reverse joystick (CH3)
#define PIN_CH_LEFT_RIGHT 3 // for left / right joystick (CH1)
#define PIN_CH_UP_DOWN 5 // for up / down joystick (CH5)

void setup() {

  // Setup receiver pins
  pinMode(PIN_CH_SNOW_FALL, INPUT);
  pinMode(PIN_CH_LEFT_RIGHT, INPUT);
  pinMode(PIN_CH_FORWARD_REVERSE, INPUT);
  pinMode(PIN_CH_UP_DOWN, INPUT);

  // Setup motor pins
  pinMode(PIN_MOTOR_RIGHT_FORWARD, OUTPUT);
  pinMode(PIN_MOTOR_RIGHT_REVERSE, OUTPUT);
  pinMode(PIN_MOTOR_LEFT_FORWARD, OUTPUT);
  pinMode(PIN_MOTOR_LEFT_REVERSE, OUTPUT);
  
  driveMotorStop();

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

  Serial.begin(9600); // Pour a bowl of Serial

}

void loop() {

  chLeftRight = pulseIn(PIN_CH_LEFT_RIGHT, HIGH, 30000); 
  chForwardReverse = pulseIn(PIN_CH_FORWARD_REVERSE, HIGH, 30000);
  chUpDown = pulseIn(PIN_CH_UP_DOWN, HIGH, 30000);
  chSnowFall = pulseIn(PIN_CH_SNOW_FALL, HIGH, 30000);

  handleMotorDirection();
  handleUpDown();
  handleSnowFall();

  printDebug();
   
}

void handleMotorDirection(){  
  if(chForwardReverse < 900){
    // lost communication do nothing
    Serial.println("LOST communication"); 
  } else { 
    driveMotorRuning = false;
    if(isInFRTopRange(chForwardReverse)){    
      driveMotorRuning = true;
      driveMotorForward();    
    } else if(isInFRBottomRange(chForwardReverse)){    
      driveMotorRuning = true;
      driveMotorReverse();    
    } else if(isInLRTopRange(chLeftRight)){    
      driveMotorRuning = true;
      driveMotorRight(); 
    } else if(isInLRBottomRange(chLeftRight)){    
      driveMotorRuning = true;   
      driveMotorLeft();    
    }
    if(!driveMotorRuning){    
      driveMotorStop();
    }
  }
}

void handleUpDown(){  
  //if(chUpDown > 1400 && chUpDown < 1500){
    // lost communication do nothing
  //} else {
    upDownMotorState = "STOP"; 
    if(chUpDown > 1800){ // switch facing down
      upDownMotorState = "REVERSE";
      digitalWrite(PIN_UP_DOWN_FORWARD,LOW);
      digitalWrite(PIN_UP_DOWN_REVERSE,HIGH);
    } else if(chUpDown < 1200 && chUpDown > 900){// switch facing up
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
  if(chSnowFall > 1400 && chSnowFall < 1500){
    // lost communication do nothing
  } else {
    if(chSnowFall > 1500){
      snowFallMotorState = "FORWARD";
      digitalWrite(PIN_SNOW_FALL_FORWARD,HIGH);
      digitalWrite(PIN_SNOW_FALL_REVERSE,LOW);
    } else if(chSnowFall > 1100 && chSnowFall < 1200){
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
    Serial.print("chLeftRight = ");
    Serial.print(chLeftRight);
    Serial.print(", chForwardReverse = ");
    Serial.print(chForwardReverse);
    Serial.print(", chUpDown = ");
    Serial.print(chUpDown);
    Serial.print(", chSnowFall = ");
    Serial.print(chSnowFall);
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
