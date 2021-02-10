#include "Arduino.h"
#include "MultiDirectionalMotor.h"

MultiDirectionalMotor::MultiDirectionalMotor(String name, int motorLeftCtrlPin, int motorRightCtrlPin, int motorLeftSpeedPin, int motorRightSpeedPin){

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
}

void MultiDirectionalMotor::forward(){
  digitalWrite(_motorLeftCtrlPin,LOW);
  digitalWrite(_motorRightCtrlPin,LOW);

  analogWrite(_motorRightSpeedPin,200);
  analogWrite(_motorLeftSpeedPin,200);
}

void MultiDirectionalMotor::reverse(){
  digitalWrite(_motorLeftCtrlPin,HIGH);
  digitalWrite(_motorRightCtrlPin,HIGH);

  analogWrite(_motorRightSpeedPin,200);
  analogWrite(_motorLeftSpeedPin,200);
}

void MultiDirectionalMotor::fullLeft(){

  digitalWrite(_motorLeftCtrlPin,HIGH);
  digitalWrite(_motorRightCtrlPin,LOW);

  analogWrite(_motorRightSpeedPin,255);
  analogWrite(_motorLeftSpeedPin,255);
}

void MultiDirectionalMotor::fullRight(){
  digitalWrite(_motorLeftCtrlPin,LOW);
  digitalWrite(_motorRightCtrlPin,HIGH);

  analogWrite(_motorRightSpeedPin,255);
  analogWrite(_motorLeftSpeedPin,255);
}

void MultiDirectionalMotor::forwardLeft(){
  digitalWrite(_motorLeftCtrlPin,LOW);
  digitalWrite(_motorRightCtrlPin,LOW);

  analogWrite(_motorRightSpeedPin,255);
  analogWrite(_motorLeftSpeedPin,200);
}

void MultiDirectionalMotor::forwardRight(){
  digitalWrite(_motorLeftCtrlPin,LOW);
  digitalWrite(_motorRightCtrlPin,LOW);

  analogWrite(_motorRightSpeedPin,200);
  analogWrite(_motorLeftSpeedPin,255);
}

void MultiDirectionalMotor::reverseLeft(){
  digitalWrite(_motorLeftCtrlPin,HIGH);
  digitalWrite(_motorRightCtrlPin,HIGH);

  analogWrite(_motorRightSpeedPin,255);
  analogWrite(_motorLeftSpeedPin,200);
}

void MultiDirectionalMotor::reverseRight(){
  digitalWrite(_motorLeftCtrlPin,HIGH);
  digitalWrite(_motorRightCtrlPin,HIGH);

  analogWrite(_motorRightSpeedPin,200);
  analogWrite(_motorLeftSpeedPin,255);
}

void MultiDirectionalMotor::stop(){
  digitalWrite(_motorLeftCtrlPin,LOW);
  digitalWrite(_motorRightCtrlPin,LOW);
  analogWrite(_motorRightSpeedPin,0);
  analogWrite(_motorLeftSpeedPin,0);
}

void MultiDirectionalMotor::_debug(String debugValue){

}
