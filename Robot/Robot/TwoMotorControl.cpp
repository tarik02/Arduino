#include "TwoMotorControl.h"

TwoMotorControl::TwoMotorControl(const unsigned char leftMotorPin1, const unsigned char leftMotorPin2, const unsigned char rightMotorPin1, const unsigned char rightMotorPin2) :
  leftMotorPin1(leftMotorPin1), leftMotorPin2(leftMotorPin2), rightMotorPin1(rightMotorPin1), rightMotorPin2(rightMotorPin2)
{
  
}

void TwoMotorControl::attach()
{
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);

  stop();
}

unsigned int TwoMotorControl::go(int distance)
{
  if (distance != 0)
  {
    unsigned int wait;
    stopTime = millis() + (wait = (abs(distance) * 100));

    if (distance > 0)
    {
      digitalWrite(leftMotorPin1, HIGH);
      digitalWrite(leftMotorPin2, LOW);
      digitalWrite(rightMotorPin1, HIGH);
      digitalWrite(rightMotorPin2, LOW);
    }
    else
    {
      digitalWrite(leftMotorPin1, LOW);
      digitalWrite(leftMotorPin2, HIGH);
      digitalWrite(rightMotorPin1, LOW);
      digitalWrite(rightMotorPin2, HIGH);
    }

    return wait;
  }

  return 0;
}

unsigned int TwoMotorControl::rotate(int degrees)
{
  if (degrees != 0)
  {
    unsigned int wait;
    stopTime = millis() + (wait = (abs(degrees) * 46));

    if (degrees > 0)
    {
      digitalWrite(leftMotorPin1, HIGH);
      digitalWrite(leftMotorPin2, LOW);
      digitalWrite(rightMotorPin1, LOW);
      digitalWrite(rightMotorPin2, HIGH);
    }
    else
    {
      digitalWrite(leftMotorPin1, LOW);
      digitalWrite(leftMotorPin2, HIGH);
      digitalWrite(rightMotorPin1, HIGH);
      digitalWrite(rightMotorPin2, LOW);
    }

    return wait;
  }

  return 0;
}

void TwoMotorControl::stop()
{
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, LOW);
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, LOW);

  stopTime = 4294967295;
}

void TwoMotorControl::tick()
{
  if (stopTime <= millis())
  {
    stop();
  }
}




