#include "Arduino.h"
#include "MdMotorWithRelay.h"

MdMotorWithRelay::MdMotorWithRelay(String name, int motorLeftForwardPin, int motorLeftReversePin, int motorRightForwardPin, int motorRightReversePin, int motorRightSpeedPin, int motorLeftSpeedPin, int turnMode){

  _name = name;
  _fixedTurnSpeed = 30;
  _turnMode = turnMode;
  _currentSpeed = 200;
  _turnOffset = 54;
  _turnMode = turnMode;

  _motorLeftOffset = 0;
  _motorRightOffset = 0;
  
  _motorLeftForwardPin = motorLeftForwardPin;
  _motorLeftReversePin = motorLeftReversePin;
  _motorRightForwardPin = motorRightForwardPin;
  _motorRightReversePin = motorRightReversePin;
  _motorRightSpeedPin = motorRightSpeedPin;
  _motorLeftSpeedPin = motorLeftSpeedPin;

}

void MdMotorWithRelay::init(){
  pinMode(_motorLeftForwardPin, OUTPUT);
  pinMode(_motorLeftReversePin, OUTPUT);
  pinMode(_motorRightForwardPin, OUTPUT);
  pinMode(_motorRightReversePin, OUTPUT);
  pinMode(_motorRightSpeedPin, OUTPUT);
  pinMode(_motorLeftSpeedPin, OUTPUT);
  analogWrite(_motorRightSpeedPin,0);
  analogWrite(_motorLeftSpeedPin,0);

  _calculateSpeed("normal", _motorRightOffset);
  _calculateSpeed("normal", _motorLeftOffset);
}

void MdMotorWithRelay::forward(){
  digitalWrite(_motorLeftForwardPin,HIGH);
  digitalWrite(_motorLeftReversePin,LOW);
  digitalWrite(_motorRightForwardPin,HIGH);
  digitalWrite(_motorRightReversePin,LOW);

  analogWrite(_motorRightSpeedPin, _calculateSpeed("normal", _motorRightOffset));
  analogWrite(_motorLeftSpeedPin, _calculateSpeed("normal", _motorLeftOffset));
}

void MdMotorWithRelay::reverse(){
  digitalWrite(_motorLeftForwardPin,LOW);
  digitalWrite(_motorLeftReversePin,HIGH);
  digitalWrite(_motorRightForwardPin,LOW);
  digitalWrite(_motorRightReversePin,HIGH);

  analogWrite(_motorRightSpeedPin, _calculateSpeed("normal", _motorRightOffset));
  analogWrite(_motorLeftSpeedPin, _calculateSpeed("normal", _motorLeftOffset));
}

void MdMotorWithRelay::fullLeft(){
  digitalWrite(_motorLeftForwardPin,LOW);
  digitalWrite(_motorLeftReversePin,HIGH);
  digitalWrite(_motorRightForwardPin,HIGH);
  digitalWrite(_motorRightReversePin,LOW);

  analogWrite(_motorRightSpeedPin, _calculateSpeed("full_turn", _motorRightOffset));
  analogWrite(_motorLeftSpeedPin, _calculateSpeed("full_turn", _motorLeftOffset));
    
}

void MdMotorWithRelay::fullRight(){
  digitalWrite(_motorLeftForwardPin,HIGH);
  digitalWrite(_motorLeftReversePin,LOW);
  digitalWrite(_motorRightForwardPin,LOW);
  digitalWrite(_motorRightReversePin,HIGH);

  // Full speed to both motor 
  analogWrite(_motorRightSpeedPin, _calculateSpeed("full_turn", _motorRightOffset));
  analogWrite(_motorLeftSpeedPin, _calculateSpeed("full_turn", _motorLeftOffset));
}

void MdMotorWithRelay::forwardLeft(){
  digitalWrite(_motorLeftForwardPin,HIGH);
  digitalWrite(_motorLeftReversePin,LOW);
  digitalWrite(_motorRightForwardPin,HIGH);
  digitalWrite(_motorRightReversePin,LOW);

  analogWrite(_motorRightSpeedPin, _calculateSpeed("turn", _motorRightOffset));
  analogWrite(_motorLeftSpeedPin, _calculateSpeed("slow_turn", _motorLeftOffset));
}

void MdMotorWithRelay::forwardRight(){
  digitalWrite(_motorLeftForwardPin,HIGH);
  digitalWrite(_motorLeftReversePin,LOW);
  digitalWrite(_motorRightForwardPin,HIGH);
  digitalWrite(_motorRightReversePin,LOW);

  analogWrite(_motorRightSpeedPin, _calculateSpeed("slow_turn", _motorRightOffset));
  analogWrite(_motorLeftSpeedPin, _calculateSpeed("turn", _motorLeftOffset));
}

void MdMotorWithRelay::reverseLeft(){
  digitalWrite(_motorLeftForwardPin,LOW);
  digitalWrite(_motorLeftReversePin,HIGH);
  digitalWrite(_motorRightForwardPin,LOW);
  digitalWrite(_motorRightReversePin,HIGH);
  
  analogWrite(_motorRightSpeedPin, _calculateSpeed("turn", _motorRightOffset));
  analogWrite(_motorLeftSpeedPin, _calculateSpeed("slow_turn", _motorLeftOffset));
}

void MdMotorWithRelay::reverseRight(){
  digitalWrite(_motorLeftForwardPin,LOW);
  digitalWrite(_motorLeftReversePin,HIGH);
  digitalWrite(_motorRightForwardPin,LOW);
  digitalWrite(_motorRightReversePin,HIGH);

  analogWrite(_motorRightSpeedPin, _calculateSpeed("slow_turn", _motorRightOffset));
  analogWrite(_motorLeftSpeedPin, _calculateSpeed("turn", _motorLeftOffset));
}

void MdMotorWithRelay::stop(){
  digitalWrite(_motorLeftForwardPin,LOW);
  digitalWrite(_motorLeftReversePin,LOW);
  digitalWrite(_motorRightForwardPin,LOW);
  digitalWrite(_motorRightReversePin,LOW);

  analogWrite(_motorRightSpeedPin,0);
  analogWrite(_motorLeftSpeedPin,0);
}

void MdMotorWithRelay::increaseSpeed(){
  _currentSpeed+=20;

  if(_currentSpeed > 255){
    _currentSpeed=255;
  }
  
  Serial.print("_currentSpeed = ");
  Serial.println(_currentSpeed);
}

void MdMotorWithRelay::decreaseSpeed(){
  _currentSpeed-=20;
  if(_currentSpeed < 0){
    _currentSpeed=0;
  }
  Serial.print("_currentSpeed = ");
  Serial.println(_currentSpeed);
}

void MdMotorWithRelay::resetSpeed(){
  _currentSpeed = 200;
  Serial.print("_currentSpeed = ");
  Serial.println(_currentSpeed);
}

int MdMotorWithRelay::_calculateSpeed(String actionType, int motorOffset){
  int calculatedSpeed=_currentSpeed;
  if(actionType == "full_turn"){
    switch (_turnMode){
      case 0:  // Current speed turn
        calculatedSpeed=(int)(_currentSpeed+motorOffset+_turnOffset);
        break;
      case 1:  // slower speed turn
        calculatedSpeed=(int)(_currentSpeed+motorOffset-_turnOffset);
        break;
      case 2:  // Fixed speed turn
        calculatedSpeed=_fixedTurnSpeed;
        break;
    }
  } else if(actionType == "turn"){
    calculatedSpeed=(int)(_currentSpeed+motorOffset+_turnOffset);
  } else if(actionType == "slow_turn"){
    calculatedSpeed=(int)(_currentSpeed+motorOffset-_turnOffset);
  } else if(actionType == "normal"){
    calculatedSpeed=(int)(_currentSpeed+motorOffset);
  }
  if(calculatedSpeed > 255){
    calculatedSpeed=255;
  }
  if(calculatedSpeed < 0){
    calculatedSpeed=0;
  }

  Serial.print("speed = ");
  Serial.println(calculatedSpeed);
  
  return calculatedSpeed;
}
