#include "Program.h"
#include "API.h"
#include "Lockscreen.h"
#include "Timer.h"
#include "flappyBird.h"

TLockScreen::TLockScreen() : TProgram(false)
{
  icon = (unsigned char *)0;
};
void TLockScreen::Start()
{
  
};
void TLockScreen::ReadButtons(byte &Buttons)
{
  if ((Buttons | _BV(2)) == Buttons)
  {
    Buttons &= ~_BV(2);
    API->RunProgram(1);
  }
};
void TLockScreen::Paint(LCD *Canvas)
{
  //Canvas->drawText(0,0,"< to unlock.");
  double LineAngle;
  int LineX,LineY;
  
  LineAngle = PI * (360 * (float(API->Time % 60) / 60) - 90) / 180.0;
  LineX = cos(LineAngle) * 18;
  LineY = sin(LineAngle) * 18;
  Canvas->drawLine(24,24,24 + LineX,24 + LineY);
  
  LineAngle = PI * (360 * (float(API->Time / 60 % 60) / 60) - 90) / 180.0;
  LineX = cos(LineAngle) * 20;
  LineY = sin(LineAngle) * 20;
  Canvas->drawLine(24,24,24 + LineX,24 + LineY);
  
  LineAngle = PI * (360 * (float(API->Time / 60 / 60 % 24) / 60) - 90) / 180.0;
  LineX = cos(LineAngle) * 13;
  LineY = sin(LineAngle) * 13;
  Canvas->drawLine(24,24,24 + LineX,24 + LineY);
};
