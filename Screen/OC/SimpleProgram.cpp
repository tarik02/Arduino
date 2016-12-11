#include "Program.h"
#include "API.h"
#include "SimpleProgram.h"
#include "Timer.h"


TSimpleProgram::TSimpleProgram() : TProgram(true)
{
  icon = (unsigned char *)SimpleProgramIcon;
};
void TSimpleProgram::Start()
{
  
};
void TSimpleProgram::ReadButtons(byte &Buttons)
{
  if ((Buttons | _BV(3)) == Buttons)
  {
    Buttons &= ~_BV(3);
  }
};
void TSimpleProgram::Paint(LCD *Canvas)
{
  
};
