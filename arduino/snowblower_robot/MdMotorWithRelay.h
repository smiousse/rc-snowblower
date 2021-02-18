#ifndef MdMotorWithRelay_h
#define MdMotorWithRelay_h

#include "Arduino.h"

class MdMotorWithRelay
{
  public:
    MdMotorWithRelay(String name, int motorLeftForwardPin, int motorLeftReversePin, int motorRightForwardPin, int motorRightReversePin, int motorRightSpeedPin, int motorLeftSpeedPin, int turnMode);

    void forward();
    void reverse();
    void fullLeft();
    void fullRight();
    void forwardLeft();
    void forwardRight();
    void reverseLeft();
    void reverseRight();
    void stop();
    void init();
    void increaseSpeed();
    void decreaseSpeed();
    void resetSpeed();

  private:
    String _name;
    int _currentAction;
    int _currentSpeed;

    int _fixedTurnSpeed;
    int _turnOffset;
    int _turnMode;

    int _motorLeftOffset;
    int _motorRightOffset;
    
    int _motorLeftForwardPin;
    int _motorLeftReversePin;
    int _motorRightForwardPin;
    int _motorRightReversePin;
    int _motorRightSpeedPin;
    int _motorLeftSpeedPin;
    int _calculateSpeed(String actionType, int motorOffset);
    void _refreshCurrentSpeed();
};

#endif
