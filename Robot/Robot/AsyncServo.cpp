#include "AsyncServo.h"

AsyncServo::AsyncServo(const unsigned char pin, unsigned char angle) :
  pin(pin),
  pos(0),
  angle(angle)
{
  init = 180;
  speed = 10;
}

void AsyncServo::attach()
{
  pinMode(pin, OUTPUT);
  //servo.attach(pin);
}

void AsyncServo::spin(unsigned char angle, unsigned char speed)
{
  this->angle = max(min(angle, 180), 0);
  this->speed = 25 - speed;
  lastUpdate = millis();
}

void AsyncServo::tick()
{
  auto diff = millis() - lastUpdate;

  /*if (micros() >= offtime)
  {
    digitalWrite(pin, LOW);
  }*/

  /*if ((init > 0) && (diff >= 5))
  {
    lastUpdate = millis();
    digitalWrite(pin, HIGH);
    delayMicroseconds((angle * 11) + 500);
    digitalWrite(pin, LOW);
    
    init--;
  }
  else*/
  {
    if (pos != angle)
    {
      if (diff >= speed)
      {
        lastUpdate = millis();
    
        //if (pos != angle)
        {
          //pos = ((pos > angle) ? max(pos - diff / speed, angle) : min(angle, pos + diff / speed));
          pos = ((pos > angle) ? pos - 1 : pos + 1);
        }
      }

      
    }

    /*digitalWrite(pin, HIGH);
    //offtime = micros() + (pos * 11) + 500;
    delayMicroseconds((pos * 11) + 500);
    digitalWrite(pin, LOW);*/
  }
}

