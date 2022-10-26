#ifndef MdMotorWithController_h
#define MdMotorWithController_h

#include "Arduino.h"
#include <SoftwareSerial.h>

class MdMotorWithController
{
  public:
    MdMotorWithController(String name);

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

    int _motorLeftOffset;
    int _motorRightOffset;

    void _refreshCurrentSpeed();
    void _serialWrite(int motorType, int speed);
};

#endif
