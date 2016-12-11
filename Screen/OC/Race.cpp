#include "Program.h"
#include "API.h"
#include "Race.h"
#include "Timer.h"


void TRaceTimer(void *Data)
{
  if ((API->buttons | _BV(1)) == API->buttons)
    ((TRace *)Data)->myY--;
  if ((API->buttons | _BV(5)) == API->buttons)
    ((TRace *)Data)->myY++;
};

TRace::TRace() : TProgram(true)
{
  icon = (unsigned char *)RaceIcon;
  
  addTimer(15,false,TRaceTimer,this);
  
  Machines[0].X = 0;
  Machines[1].X = 1;
  Machines[2].X = 2;
  Machines[3].X = 3;
  Machines[4].X = 4;
  
  Machines[0].Y = 0;
  Machines[1].Y = 5;
  Machines[2].Y = 15;
  Machines[3].Y = 10;
  Machines[4].Y = 20;
  
  myX = 0;
  myY = 30;
  destX = 0;
};
void TRace::Start()
{
  
};
void TRace::ReadButtons(byte &Buttons)
{
  if ((Buttons | _BV(2)) == Buttons)
  {
    Buttons &= ~_BV(2);
    destX -= 13;
  }
  if ((Buttons | _BV(3)) == Buttons)
  {
    Buttons &= ~_BV(3);
  }
  if ((Buttons | _BV(4)) == Buttons)
  {
    Buttons &= ~_BV(4);
    destX += 13;
  }
};
void TRace::Paint(LCD *Canvas)
{
  for (int i = 0; i < 7; i++)
    Canvas->drawVLine(2 + i * 13,0,47);
  
  Canvas->drawBitmapPGM(3 + myX,myY,12,17,MachineImage1);
  
  for (int i = 0; i < sizeof(Machines) / sizeof(Machines[0]); i++)
  {
    Canvas->drawBitmapPGM(3 + Machines[i].X * 13,Machines[i].Y,12,17,MachineImage2);
  };
  
  if (myX < destX)
    myX += 2;
  else if (myX > destX)
    myX -= 2;
  
  if (abs(myX - destX) == 1)
    myX = destX;
};
