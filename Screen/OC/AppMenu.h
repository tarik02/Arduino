#ifndef _PROGRAM_APPMENU_
#define _PROGRAM_APPMENU_
#include <Arduino.h>

class TAppMenu : public TProgram
{
  private:
  int selID;
  public:
  TAppMenu();
  
  void Start();
  void ReadButtons(byte &Buttons);
  void Paint(LCD *Canvas);
};

#endif

