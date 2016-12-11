#include "Program.h"
#include "API.h"
#include "Taras.h"
#include "Timer.h"


TTaras::TTaras() : TProgram(true)
{
  icon = (unsigned char *)TarasIcon;
};
void TTaras::Start()
{
  
};
void TTaras::ReadButtons(byte &Buttons)
{
  if ((Buttons | _BV(3)) == Buttons)
  {
    Buttons &= ~_BV(3);
  }
};
void TTaras::Paint(LCD *Canvas)
{
  Canvas->drawBitmapPGM(0,0,84,48,Taras);
};
