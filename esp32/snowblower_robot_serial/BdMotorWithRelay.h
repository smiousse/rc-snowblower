#ifndef BdMotorWithRelay_h
#define BdMotorWithRelay_h

#include "Arduino.h"

// Bi direction motor forward or reverse
class BdMotorWithRelay
{
  public:
    BdMotorWithRelay(String name, int motorForwardPin, int motorReversePin, int motorSpeedPin);

    void forward();
    void reverse();

    void stop();
    void init();
    void increaseSpeed();
    void decreaseSpeed();
    void resetSpeed();

  private:
    String _name;
    int _currentSpeed;  
    int _motorForwardPin;
    int _motorReversePin;
    int _motorSpeedPin;
};

#endif
