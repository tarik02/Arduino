#include "LCD.h"
#include "Program.h"

#include "API.h"
/*
namespace API
{
  void RunProgram(int ID)
  {
    curProgram = ID;
  };
  void Render(LCD *Canvas)
  {
    Canvas->clear();
    ((TProgram *)Programs->GetItem(curProgram))->Paint(Canvas);
    Canvas->display();
  };
};
*/

_API *API;

_API::_API()
{
  curProgram = -1;
  Programs = new TList();
};

void _API::Run()
{
  //RunProgram(0);
  RunProgram(0);
}
void _API::RunProgram(int ID)
{
  curProgram = ID;
  ((TProgram *)Programs->GetItem(curProgram))->Start();
};
void _API::Render(LCD *Canvas)
{
  if (curProgram == -1) { return; }
  
  ((TProgram *)Programs->GetItem(curProgram))->Paint(Canvas);
};
void _API::ReadButtons(byte &Buttons)
{
  buttons = Buttons;
  
  Time = millis() / 1000;
  
  if (curProgram == -1) { return; }
  
  if ((Buttons | _BV(6)) == Buttons)
  {
    Buttons &= ~_BV(6);
    RunProgram(0);
  }
  else
  {
    ((TProgram *)Programs->GetItem(curProgram))->ReadButtons(Buttons);
  };
};

