#ifndef _PROGRAM_LOCKSCREEN_
#define _PROGRAM_LOCKSCREEN_
#include <Arduino.h>

class TLockScreen : public TProgram
{
  private:
  
  public:
  TLockScreen();
  
  void Start();
  void ReadButtons(byte &Buttons);
  void Paint(LCD *Canvas);
};
#endif

