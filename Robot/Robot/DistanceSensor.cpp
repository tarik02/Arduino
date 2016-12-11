#include "DistanceSensor.h"

DistanceSensor::DistanceSensor(const unsigned char echoPin, const unsigned char trigPin) :
  echoPin(echoPin), trigPin(trigPin)
{
  
}

void DistanceSensor::attach()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

unsigned int DistanceSensor::read()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  auto dist = pulseIn(echoPin, HIGH, 10000) / 58;
  
  return (dist == 0) ? DISTANCE_FAR : dist;
}



