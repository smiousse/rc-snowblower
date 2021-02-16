#include "Arduino.h"
#include "MultiDirectionalMotor.h"

MultiDirectionalMotor::MultiDirectionalMotor(String name, int motorLeftCtrlPin, int motorRightCtrlPin, int motorLeftSpeedPin, int motorRightSpeedPin){

  _currentSpeed = 200;
  _turnOffset = 54;

  _motorLeftOffset = 0;
  _motorRightOffset = 10;

  _name = name;
  _motorLeftCtrlPin = motorLeftCtrlPin;
  _motorRightCtrlPin = motorRightCtrlPin;
  _motorRightSpeedPin = motorRightSpeedPin;
  _motorLeftSpeedPin = motorLeftSpeedPin;

}

void MultiDirectionalMotor::init(){

  pinMode(_motorLeftCtrlPin, OUTPUT);
  pinMode(_motorRightCtrlPin, OUTPUT);

  pinMode(_motorRightSpeedPin, OUTPUT);
  pinMode(_motorLeftSpeedPin, OUTPUT);

  stop();
  _calculateSpeed("normal", _motorRightOffset);
  _calculateSpeed("normal", _motorLeftOffset);
}

void MultiDirectionalMotor::forward(){
  digitalWrite(_motorLeftCtrlPin,LOW);
  digitalWrite(_motorRightCtrlPin,LOW);

  analogWrite(_motorRightSpeedPin, _calculateSpeed("normal", _motorRightOffset));
  analogWrite(_motorLeftSpeedPin, _calculateSpeed("normal", _motorLeftOffset));
}

void MultiDirectionalMotor::reverse(){
  digitalWrite(_motorLeftCtrlPin,HIGH);
  digitalWrite(_motorRightCtrlPin,HIGH);

  analogWrite(_motorRightSpeedPin, _calculateSpeed("normal", _motorRightOffset));
  analogWrite(_motorLeftSpeedPin, _calculateSpeed("normal", _motorLeftOffset));
}

void MultiDirectionalMotor::fullLeft(){

  digitalWrite(_motorLeftCtrlPin,HIGH);
  digitalWrite(_motorRightCtrlPin,LOW);

  analogWrite(_motorRightSpeedPin, _calculateSpeed("turn", _motorRightOffset));
  analogWrite(_motorLeftSpeedPin, _calculateSpeed("turn", _motorLeftOffset));
}

void MultiDirectionalMotor::fullRight(){
  digitalWrite(_motorLeftCtrlPin,LOW);
  digitalWrite(_motorRightCtrlPin,HIGH);

  analogWrite(_motorRightSpeedPin, _calculateSpeed("turn", _motorRightOffset));
  analogWrite(_motorLeftSpeedPin, _calculateSpeed("turn", _motorLeftOffset));
}

void MultiDirectionalMotor::forwardLeft(){
  digitalWrite(_motorLeftCtrlPin,LOW);
  digitalWrite(_motorRightCtrlPin,LOW);

  analogWrite(_motorRightSpeedPin, _calculateSpeed("turn", _motorRightOffset));
  analogWrite(_motorLeftSpeedPin, _calculateSpeed("slow_turn", _motorLeftOffset));
}

void MultiDirectionalMotor::forwardRight(){
  digitalWrite(_motorLeftCtrlPin,LOW);
  digitalWrite(_motorRightCtrlPin,LOW);

  analogWrite(_motorRightSpeedPin, _calculateSpeed("slow_turn", _motorRightOffset));
  analogWrite(_motorLeftSpeedPin, _calculateSpeed("turn", _motorLeftOffset));
}

void MultiDirectionalMotor::reverseLeft(){
  digitalWrite(_motorLeftCtrlPin,HIGH);
  digitalWrite(_motorRightCtrlPin,HIGH);

  analogWrite(_motorRightSpeedPin, _calculateSpeed("turn", _motorRightOffset));
  analogWrite(_motorLeftSpeedPin, _calculateSpeed("slow_turn", _motorLeftOffset));
}

void MultiDirectionalMotor::reverseRight(){
  digitalWrite(_motorLeftCtrlPin,HIGH);
  digitalWrite(_motorRightCtrlPin,HIGH);

  analogWrite(_motorRightSpeedPin, _calculateSpeed("slow_turn", _motorRightOffset));
  analogWrite(_motorLeftSpeedPin, _calculateSpeed("turn", _motorLeftOffset));
}

void MultiDirectionalMotor::stop(){
  digitalWrite(_motorLeftCtrlPin,LOW);
  digitalWrite(_motorRightCtrlPin,LOW);
  analogWrite(_motorRightSpeedPin,0);
  analogWrite(_motorLeftSpeedPin,0);
}

void MultiDirectionalMotor::increaseSpeed(){
  _currentSpeed+=20;

  if(_currentSpeed > 255){
    _currentSpeed=255;
  }
  
  Serial.print("_currentSpeed = ");
  Serial.println(_currentSpeed);
}

void MultiDirectionalMotor::decreaseSpeed(){
  _currentSpeed-=20;
  if(_currentSpeed < 0){
    _currentSpeed=0;
  }
  Serial.print("_currentSpeed = ");
  Serial.println(_currentSpeed);
}

void MultiDirectionalMotor::resetSpeed(){
  _currentSpeed = 200;
  Serial.print("_currentSpeed = ");
  Serial.println(_currentSpeed);
}

void MultiDirectionalMotor::_debug(String debugValue){

}

int MultiDirectionalMotor::_calculateSpeed(String actionType, int motorOffset){
 
  int speed=_currentSpeed;
  if(actionType == "turn"){
    speed=(int)(_currentSpeed+motorOffset+_turnOffset);
  } else if(actionType == "slow_turn"){
    speed=(int)(_currentSpeed+motorOffset-_turnOffset);
  } else if(actionType == "normal"){
    speed=(int)(_currentSpeed+motorOffset);
  }
  if(speed > 255){
    speed=255;
  }
  if(speed < 0){
    speed=0;
  }

  Serial.print("speed = ");
  Serial.println(speed);
  
  return speed;
}
