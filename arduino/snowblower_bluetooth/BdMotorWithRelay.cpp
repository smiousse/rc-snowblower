#include "Arduino.h"
#include "BdMotorWithRelay.h"

BdMotorWithRelay::BdMotorWithRelay(String name, int motorForwardPin, int motorReversePin, int motorSpeedPin){
  _name = name;
  _currentSpeed = 200;  
  _motorForwardPin = motorForwardPin;
  _motorReversePin = motorReversePin;
  _motorSpeedPin = motorSpeedPin;
}

void BdMotorWithRelay::init(){
  pinMode(_motorForwardPin, OUTPUT);
  pinMode(_motorReversePin, OUTPUT);
  if(_motorSpeedPin > 0){
    pinMode(_motorSpeedPin, OUTPUT);
    analogWrite(_motorSpeedPin, 0);
  }
}

void BdMotorWithRelay::forward(){
  digitalWrite(_motorForwardPin,HIGH);
  digitalWrite(_motorReversePin,LOW);
  if(_motorSpeedPin > 0){
    analogWrite(_motorSpeedPin, _currentSpeed);
  }  
}

void BdMotorWithRelay::reverse(){
  digitalWrite(_motorForwardPin,LOW);
  digitalWrite(_motorReversePin,HIGH);
  if(_motorSpeedPin > 0){
    analogWrite(_motorSpeedPin, _currentSpeed);
  }
}

void BdMotorWithRelay::stop(){
  digitalWrite(_motorForwardPin,LOW);
  digitalWrite(_motorReversePin,LOW);
  if(_motorSpeedPin > 0){
    analogWrite(_motorSpeedPin, 0);
  }
}

void BdMotorWithRelay::increaseSpeed(){
  _currentSpeed+=20;

  if(_currentSpeed > 255){
    _currentSpeed=255;
  }
  
  Serial.print("_currentSpeed = ");
  Serial.println(_currentSpeed);
}

void BdMotorWithRelay::decreaseSpeed(){
  _currentSpeed-=20;
  if(_currentSpeed < 0){
    _currentSpeed=0;
  }
  Serial.print("_currentSpeed = ");
  Serial.println(_currentSpeed);
}

void BdMotorWithRelay::resetSpeed(){
  _currentSpeed = 200;
  Serial.print("_currentSpeed = ");
  Serial.println(_currentSpeed);
}
