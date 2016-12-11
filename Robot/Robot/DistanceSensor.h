#ifndef DISTANCESENSOR_H
#define DISTANCESENSOR_H

#include <Arduino.h>

#define DISTANCE_FAR 65535

class DistanceSensor
{
private:
  const unsigned char echoPin, trigPin;
public:
  DistanceSensor(const unsigned char echoPin, const unsigned char trigPin);

  void attach();
  
  unsigned int read();
};

#endif
