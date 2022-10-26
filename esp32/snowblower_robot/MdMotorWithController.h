#ifndef MdMotorWithController_h
#define MdMotorWithController_h

#include "Arduino.h"

class MdMotorWithController
{
  public:
    MdMotorWithController(String name, int motorLeftCtrlPin, int motorRightCtrlPin, int motorLeftSpeedPin, int motorRightSpeedPin, int turnMode);

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

    bool isForward();
    bool isReverse();

  private:
    String _name;
    int _currentAction;
    int _fixedAction;
    int _currentSpeed;

    int _fixedTurnSpeed;
    int _turnOffset;
    int _turnMode;

    int _motorLeftOffset;
    int _motorRightOffset;

    int _motorLeftCtrlPin;
    int _motorRightCtrlPin;
    int _motorRightSpeedPin;
    int _motorLeftSpeedPin;
    int _calculateSpeed(String actionType, int motorOffset);
    void _refreshCurrentSpeed();
};

#endif
