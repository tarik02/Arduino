#ifndef ASYNCSERVO_H
#define ASYNCSERVO_H

#include <Arduino.h>

class AsyncServo
{
private:
  const unsigned char pin;

  unsigned char speed;

  unsigned char angle;
  unsigned char pos;

  unsigned long lastUpdate;
  unsigned char init;

  //unsigned long offtime;
public:
  AsyncServo(const unsigned char, unsigned char = 0);

  void attach();

  void spin(unsigned char, unsigned char = 10);
  inline unsigned char getPos() const { return pos; };
  inline unsigned char getAngle() const { return angle; };
  
  void tick();
};

#endif
