#ifndef TWOMOTORCONTROL_H
#define TWOMOTORCONTROL_H

#include <Arduino.h>

class TwoMotorControl
{
private:
  const unsigned char leftMotorPin1, leftMotorPin2;
  const unsigned char rightMotorPin1, rightMotorPin2;

  unsigned long stopTime;

  unsigned char mode;
public:
  TwoMotorControl(const unsigned char leftMotorPin1, const unsigned char leftMotorPin2, const unsigned char rightMotorPin1, const unsigned char rightMotorPin2);

  void attach();

  unsigned int go(int distance);
  unsigned int rotate(int degrees);
  void stop();
  
  void tick();
};

#endif
