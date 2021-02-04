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
int chSpeed;

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
#define PIN_CH_SPEED 6 
// N_LOW = Neutral lower, N_TOP = Neutral greater, LC_LOW = Lost communication lower, LC_TOP = Lost communication top

//                            N_LOW    N_TOP   TOP      LOW      LC_LOW  LC_TOP
int RC_LEFT_RIGHT[6]      = { 1588,    1610,   2117,    1116,    1488,   1495};
int RC_FORWARD_REVERSE[6] = { 1509,    1512,   2019,    1025,     894,    901};
int RC_UP_DOWN[6]         = { 1480,    1490,   1989,     995,       0,      0};
int RC_SNOW_FALL[6]       = { 1611,    1617,   2109,    1109,       0,      0};
int RC_SPEED[6]           = {    0,       0,   1989,     995,       0,      0};

void setup() {

  // Setup receiver pins
  pinMode(PIN_CH_SNOW_FALL, INPUT);
  pinMode(PIN_CH_LEFT_RIGHT, INPUT);
  pinMode(PIN_CH_FORWARD_REVERSE, INPUT);
  pinMode(PIN_CH_UP_DOWN, INPUT);
  pinMode(PIN_CH_SPEED, INPUT);

  // Setup motor pins
  pinMode(PIN_MOTOR_RIGHT_FORWARD, OUTPUT);
  pinMode(PIN_MOTOR_RIGHT_REVERSE, OUTPUT);
  pinMode(PIN_MOTOR_LEFT_FORWARD, OUTPUT);
  pinMode(PIN_MOTOR_LEFT_REVERSE, OUTPUT);
  
  driveMotorStop();

  // Setup snowfall motor pins
  //pinMode(PIN_SNOW_FALL_FORWARD, OUTPUT);
  //pinMode(PIN_SNOW_FALL_REVERSE, OUTPUT);
  
  //digitalWrite(PIN_SNOW_FALL_FORWARD,LOW);
  //digitalWrite(PIN_SNOW_FALL_REVERSE,LOW);

    // Setup up/down motor pins
  //pinMode(PIN_UP_DOWN_FORWARD, OUTPUT);
  //pinMode(PIN_UP_DOWN_REVERSE, OUTPUT);
  
  //digitalWrite(PIN_UP_DOWN_FORWARD,LOW);
  //digitalWrite(PIN_UP_DOWN_REVERSE,LOW);

  Serial.begin(9600); // Pour a bowl of Serial

}

void loop() {

  chLeftRight = pulseIn(PIN_CH_LEFT_RIGHT, HIGH, 30000); 
  chForwardReverse = pulseIn(PIN_CH_FORWARD_REVERSE, HIGH, 30000); 
  chUpDown = pulseIn(PIN_CH_UP_DOWN, HIGH, 30000); 
  chSnowFall = pulseIn(PIN_CH_SNOW_FALL, HIGH, 30000); 
  chSpeed = pulseIn(PIN_CH_SPEED, HIGH, 30000);

  //handleMotorDirection();
  //handleUpDown();
  //handleSnowFall();

  //printDebug();

  Serial.print(convertToPercent(chLeftRight, RC_LEFT_RIGHT));
  Serial.println("%");
  delay(1000);
   
}
//                            N_LOW    N_TOP   TOP      LOW      LC_LOW  LC_TOP
int convertToPercent(int chValue, int chConfig[]){

  Serial.print("chValue = ");
  Serial.print(chValue);
  Serial.print(" ");
  if(chValue >= chConfig[4] && chValue <= chConfig[5]){
    // Lost communication
    return 999;
  }

  if(chValue >= chConfig[0] && chValue <= chConfig[1]){
    // Neutral
    return 0;
  }

  //Serial.print(", chConfig[3] = ");
  //Serial.print(chConfig[3]);
  //Serial.print(", chConfig[0] = ");
  //Serial.print(chConfig[0]);
  //Serial.print(" ");

  if(chValue > chConfig[3] &&  chValue < chConfig[0]){
    // Lower
    int full = chConfig[0] - chConfig[3];
    int part = chConfig[0] - chValue;

    Serial.print(", full = ");
    Serial.print(full);
    Serial.print(", part = ");
    Serial.print(part);
    Serial.print(" ");
    
    return -(abs(part*100/full));
  }

  if(chValue > chConfig[1] &&  chValue < chConfig[2]){
    // Upper
    int full = chConfig[2] - chConfig[1];
    int part = -(chConfig[1] - chValue);

    Serial.print(", full = ");
    Serial.print(full);
    Serial.print(", part = ");
    Serial.print(part);
    Serial.print(" ");
    
    return abs(part*100/full);
  }
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
    Serial.print("LR = ");
    Serial.print(chLeftRight);
    Serial.print(" (");
    Serial.print(convertToPercent(chLeftRight, RC_LEFT_RIGHT));
    Serial.print("%), FR = ");
    Serial.print(chForwardReverse);
    Serial.print(" (");
    Serial.print(convertToPercent(chForwardReverse, RC_FORWARD_REVERSE));
    Serial.print("%), UD = ");
    Serial.print(chUpDown);
    Serial.print(" (");
    Serial.print(convertToPercent(chUpDown, RC_UP_DOWN));
    Serial.print("%), SF = ");
    Serial.print(chSnowFall);
    Serial.print(" (");
    Serial.print(convertToPercent(chSnowFall, RC_SNOW_FALL));
    Serial.print("%), SPEED = ");
    Serial.print(chSpeed);
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
