#ifndef _PROGRAM_
#define _PROGRAM_
#include "LCD.h"
#include <Arduino.h>
#include <avr/pgmspace.h>

class TProgram
{
  private:
  public:
  TProgram(bool fVisible) : Visible(fVisible) {  };
  // 18 13
  
  //uint8_t icon[39];
  unsigned char *icon;
  
  virtual void Start();
  virtual void ReadButtons(byte &Buttons);
  virtual void Paint(LCD *Canvas);
  
  bool Visible;
};
#endif

