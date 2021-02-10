#ifndef MultiDirectionalMotor_h
#define MultiDirectionalMotor_h

#include "Arduino.h"

class MultiDirectionalMotor
{
  public:
    MultiDirectionalMotor(String name, int motorLeftForwardPin, int motorLeftReversePin, int motorRightForwardPin, int motorRightReversePin, int motorRightSpeedPin, int motorLeftSpeedPin);

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

  private:
    String _name;
    int _motorLeftForwardPin;
    int _motorLeftReversePin;
    int _motorRightForwardPin;
    int _motorRightReversePin;
    int _motorRightSpeedPin;
    int _motorLeftSpeedPin;
    void _debug(String debugValue);
};

#endif