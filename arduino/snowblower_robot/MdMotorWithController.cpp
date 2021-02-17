#include "Arduino.h"
#include "MdMotorWithController.h"

MdMotorWithController::MdMotorWithController(String name, int motorLeftCtrlPin, int motorRightCtrlPin, int motorLeftSpeedPin, int motorRightSpeedPin, int turnMode){

  _fixedTurnSpeed = 130;
  _currentSpeed = 200;
  _turnOffset = 54;
  _turnMode = turnMode;

  _motorLeftOffset = 0;
  _motorRightOffset = 0;

  _name = name;
  _turnMode = turnMode;
  _motorLeftCtrlPin = motorLeftCtrlPin;
  _motorRightCtrlPin = motorRightCtrlPin;
  _motorRightSpeedPin = motorRightSpeedPin;
  _motorLeftSpeedPin = motorLeftSpeedPin;

}

void MdMotorWithController::init(){

  pinMode(_motorLeftCtrlPin, OUTPUT);
  pinMode(_motorRightCtrlPin, OUTPUT);

  pinMode(_motorRightSpeedPin, OUTPUT);
  pinMode(_motorLeftSpeedPin, OUTPUT);

  stop();
  _calculateSpeed("normal", _motorRightOffset);
  _calculateSpeed("normal", _motorLeftOffset);
}

void MdMotorWithController::forward(){
  digitalWrite(_motorLeftCtrlPin,LOW);
  digitalWrite(_motorRightCtrlPin,LOW);

  analogWrite(_motorRightSpeedPin, _calculateSpeed("normal", _motorRightOffset));
  analogWrite(_motorLeftSpeedPin, _calculateSpeed("normal", _motorLeftOffset));
}

void MdMotorWithController::reverse(){
  digitalWrite(_motorLeftCtrlPin,HIGH);
  digitalWrite(_motorRightCtrlPin,HIGH);

  analogWrite(_motorRightSpeedPin, _calculateSpeed("normal", _motorRightOffset));
  analogWrite(_motorLeftSpeedPin, _calculateSpeed("normal", _motorLeftOffset));
}

void MdMotorWithController::fullLeft(){

  digitalWrite(_motorLeftCtrlPin,HIGH);
  digitalWrite(_motorRightCtrlPin,LOW);

  analogWrite(_motorRightSpeedPin, _calculateSpeed("full_turn", _motorRightOffset));
  analogWrite(_motorLeftSpeedPin, _calculateSpeed("full_turn", _motorLeftOffset));
}

void MdMotorWithController::fullRight(){
  digitalWrite(_motorLeftCtrlPin,LOW);
  digitalWrite(_motorRightCtrlPin,HIGH);

  analogWrite(_motorRightSpeedPin, _calculateSpeed("full_turn", _motorRightOffset));
  analogWrite(_motorLeftSpeedPin, _calculateSpeed("full_turn", _motorLeftOffset));
}

void MdMotorWithController::forwardLeft(){
  digitalWrite(_motorLeftCtrlPin,LOW);
  digitalWrite(_motorRightCtrlPin,LOW);

  analogWrite(_motorRightSpeedPin, _calculateSpeed("turn", _motorRightOffset));
  analogWrite(_motorLeftSpeedPin, _calculateSpeed("slow_turn", _motorLeftOffset));
}

void MdMotorWithController::forwardRight(){
  digitalWrite(_motorLeftCtrlPin,LOW);
  digitalWrite(_motorRightCtrlPin,LOW);

  analogWrite(_motorRightSpeedPin, _calculateSpeed("slow_turn", _motorRightOffset));
  analogWrite(_motorLeftSpeedPin, _calculateSpeed("turn", _motorLeftOffset));
}

void MdMotorWithController::reverseLeft(){
  digitalWrite(_motorLeftCtrlPin,HIGH);
  digitalWrite(_motorRightCtrlPin,HIGH);

  analogWrite(_motorRightSpeedPin, _calculateSpeed("turn", _motorRightOffset));
  analogWrite(_motorLeftSpeedPin, _calculateSpeed("slow_turn", _motorLeftOffset));
}

void MdMotorWithController::reverseRight(){
  digitalWrite(_motorLeftCtrlPin,HIGH);
  digitalWrite(_motorRightCtrlPin,HIGH);

  analogWrite(_motorRightSpeedPin, _calculateSpeed("slow_turn", _motorRightOffset));
  analogWrite(_motorLeftSpeedPin, _calculateSpeed("turn", _motorLeftOffset));
}

void MdMotorWithController::stop(){
  digitalWrite(_motorLeftCtrlPin,LOW);
  digitalWrite(_motorRightCtrlPin,LOW);
  analogWrite(_motorRightSpeedPin,0);
  analogWrite(_motorLeftSpeedPin,0);
}

void MdMotorWithController::increaseSpeed(){
  _currentSpeed+=20;

  if(_currentSpeed > 255){
    _currentSpeed=255;
  }
  
  Serial.print("_currentSpeed = ");
  Serial.println(_currentSpeed);
}

void MdMotorWithController::decreaseSpeed(){
  _currentSpeed-=20;
  if(_currentSpeed < 0){
    _currentSpeed=0;
  }
  Serial.print("_currentSpeed = ");
  Serial.println(_currentSpeed);
}

void MdMotorWithController::resetSpeed(){
  _currentSpeed = 200;
  Serial.print("_currentSpeed = ");
  Serial.println(_currentSpeed);
}

int MdMotorWithController::_calculateSpeed(String actionType, int motorOffset){
 
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
        calculatedSpeed=(int)(_fixedTurnSpeed+motorOffset);
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
