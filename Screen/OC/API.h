#ifndef _API_
#define _API_
#include "List.h"

class _API
{
  public:
  _API();
  int curProgram;
  TList *Programs;
  
  void Run();
  void RunProgram(int ID);
  void Render(LCD *Canvas);
  void ReadButtons(byte &Buttons);
  
  uint64_t Time;
  
  byte buttons;
};

extern _API *API;

#endif
