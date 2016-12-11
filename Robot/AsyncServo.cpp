#include "Servo.h"

Servo::Servo(const unsigned char pin) :
  pin(pin),
  pos(0),
  timer1(0),
  timer2(0)
{
  pinMode(pin, OUTPUT);
}

void Servo::spin(unsigned char angle, unsigned char speed)
{
  this->angle = angle;
  this->speed = 25 - speed;
  lasttime = millis();
}

void Servo::tick()
{
  unsigned long diff = millis() - lasttime;
  lasttime = millis();

  if (timer1 > 0)
  {
    timer1 -= diff;

    if (timer1 <= 0)
    {
      digitalWrite(pin, LOW);
      timer1 = 0;
    }

    return;
  }

  if (timer2 > 0)
  {
    timer2 -= diff;

    if (timer2 <= 0)
    {
      timer2 = 0;
    }

    return;
  }
  
  Serial.print(pos);
  Serial.print(" ");
  Serial.println(angle);
  
  if (pos != angle)
  {
    (pos > angle) ? pos-- : pos++;
    
    digitalWrite(pin, HIGH);

    timer1 = ((pos * 11) + 500) / 1000;
    timer2 = speed;
  }
}

