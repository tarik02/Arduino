#ifndef SERVO_H
#define SERVO_H

#include <Arduino.h>
#include "Scheduler.h"

class Servo
{
private:
  const unsigned char pin;
  
  unsigned int pos;

  unsigned int angle;
  unsigned int speed;

  unsigned long lasttime;
  unsigned int timer1, timer2;
public:
  Servo(const unsigned char pin);

  void spin(unsigned char angle, unsigned char speed = 15);
  void tick();
};

#endif
