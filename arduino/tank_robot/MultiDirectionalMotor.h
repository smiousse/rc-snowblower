#ifndef MultiDirectionalMotor_h
#define MultiDirectionalMotor_h

#include "Arduino.h"

class MultiDirectionalMotor
{
  public:
    MultiDirectionalMotor(String name, int motorLeftCtrlPin, int motorRightCtrlPin, int motorLeftSpeedPin, int motorRightSpeedPin);

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
    int _motorLeftCtrlPin;
    int _motorRightCtrlPin;
    int _motorRightSpeedPin;
    int _motorLeftSpeedPin;
    void _debug(String debugValue);
};

#endif