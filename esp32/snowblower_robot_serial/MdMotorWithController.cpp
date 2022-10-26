#include "Arduino.h"
#include "MdMotorWithController.h"
#include <SoftwareSerial.h>

#define AC_STOP 0
#define AC_FORWARD 1
#define AC_REVERSE 2
#define AC_TURN 3

#define DEFAULT_SPEED 30

// Robot motor pins
#define RX_PIN 3  //define direction control pin of left motor controller RX
#define TX_PIN 1   //define PWM control pin of left motor controller pin TX

#define MOTOR_TYPE_LEFT 0
#define MOTOR_TYPE_RIGHT 1

#define MOTOR_STOP_VALUE 127
#define SERIAL_HEADER_VALUE 85

SoftwareSerial MDDS60Serial(RX_PIN, TX_PIN);

MdMotorWithController::MdMotorWithController(String name){

  _fixedTurnSpeed = 32;
  _currentAction = AC_STOP;
  _fixedAction = AC_STOP;
  _currentSpeed = DEFAULT_SPEED;
  _turnOffset = 10;

  _motorLeftOffset = 0;
  _motorRightOffset = 0;

  _name = name;
}

void MdMotorWithController::init(){
  MDDS60Serial.begin(9600);
  stop();
}

void MdMotorWithController::forward(){
  _currentAction = AC_FORWARD;  
  _fixedAction = AC_FORWARD;

  _serialWrite(MOTOR_TYPE_LEFT, MOTOR_STOP_VALUE + _currentSpeed);
  _serialWrite(MOTOR_TYPE_RIGHT, MOTOR_STOP_VALUE + _currentSpeed);

}

void MdMotorWithController::reverse(){
  _currentAction = AC_REVERSE;
  _fixedAction = AC_REVERSE;
  
  _serialWrite(MOTOR_TYPE_LEFT, MOTOR_STOP_VALUE - _currentSpeed);
  _serialWrite(MOTOR_TYPE_RIGHT, MOTOR_STOP_VALUE - _currentSpeed);
}

void MdMotorWithController::fullLeft(){
  _currentAction = AC_TURN;
  _serialWrite(MOTOR_TYPE_LEFT, MOTOR_STOP_VALUE - _fixedTurnSpeed);
  _serialWrite(MOTOR_TYPE_RIGHT, MOTOR_STOP_VALUE + _fixedTurnSpeed);
}

void MdMotorWithController::fullRight(){
  _currentAction = AC_TURN;
  _serialWrite(MOTOR_TYPE_LEFT, MOTOR_STOP_VALUE + _fixedTurnSpeed);
  _serialWrite(MOTOR_TYPE_RIGHT, MOTOR_STOP_VALUE - _fixedTurnSpeed);
}

void MdMotorWithController::forwardLeft(){
  _currentAction = AC_TURN;
  _serialWrite(MOTOR_TYPE_LEFT, MOTOR_STOP_VALUE + _currentSpeed);
  _serialWrite(MOTOR_TYPE_RIGHT, MOTOR_STOP_VALUE + _currentSpeed + _turnOffset);
}

void MdMotorWithController::forwardRight(){
  _currentAction = AC_TURN;
  _serialWrite(MOTOR_TYPE_LEFT, MOTOR_STOP_VALUE + _currentSpeed + _turnOffset);
  _serialWrite(MOTOR_TYPE_RIGHT, MOTOR_STOP_VALUE + _currentSpeed);
}

void MdMotorWithController::reverseLeft(){
  _currentAction = AC_TURN;
  _serialWrite(MOTOR_TYPE_LEFT, MOTOR_STOP_VALUE - _currentSpeed);
  _serialWrite(MOTOR_TYPE_RIGHT, MOTOR_STOP_VALUE - _currentSpeed - _turnOffset);
}

void MdMotorWithController::reverseRight(){
  _currentAction = AC_TURN;
  _serialWrite(MOTOR_TYPE_LEFT, MOTOR_STOP_VALUE - _currentSpeed - _turnOffset);
  _serialWrite(MOTOR_TYPE_RIGHT, MOTOR_STOP_VALUE - _currentSpeed);
}

void MdMotorWithController::stop(){
  _currentAction = AC_STOP;
  _fixedAction = AC_STOP;
  _serialWrite(MOTOR_TYPE_LEFT, MOTOR_STOP_VALUE);
  _serialWrite(MOTOR_TYPE_RIGHT, MOTOR_STOP_VALUE);
}

void MdMotorWithController::increaseSpeed(){
  _currentSpeed+=10;
  if(_currentSpeed > 255){
    _currentSpeed=255;
  }  
  _refreshCurrentSpeed();
}

void MdMotorWithController::decreaseSpeed(){
  _currentSpeed-=10;
  if(_currentSpeed < 0){
    _currentSpeed=0;
  }
  //Serial.print("_currentSpeed = ");
  //Serial.println(_currentSpeed);
  _refreshCurrentSpeed();
}

void MdMotorWithController::resetSpeed(){
  _currentSpeed = DEFAULT_SPEED;
  //Serial.print("_currentSpeed = ");
 // Serial.println(_currentSpeed);
  _refreshCurrentSpeed();
}

bool MdMotorWithController::isForward(){
  return _fixedAction == AC_FORWARD;
}

bool MdMotorWithController::isReverse(){
  return _fixedAction == AC_REVERSE;
}

void MdMotorWithController::_refreshCurrentSpeed(){
  switch (_currentAction){
    case AC_FORWARD:
      forward();
      break;
    case AC_REVERSE: 
      reverse();
      break;
  }
}

void MdMotorWithController::_serialWrite(int motorType, int speed){
  MDDS60Serial.write(SERIAL_HEADER_VALUE); // 1st byte: Header.

  if(speed > 255){
    speed=255;
  }
  if(speed < 0){
    speed=0;
  }
  
  if(motorType == MOTOR_TYPE_LEFT){
    MDDS60Serial.write((byte)0); // 2nd byte: Channel = left & Address = 0.
    MDDS60Serial.write(speed);
    MDDS60Serial.write(SERIAL_HEADER_VALUE + speed);
  } else { // right motore
    MDDS60Serial.write(8); // 2nd byte: Channel = right & Address = 0.
    MDDS60Serial.write(speed);
    MDDS60Serial.write(SERIAL_HEADER_VALUE + 8 + speed);    
  }
  
}
