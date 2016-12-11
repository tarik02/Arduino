#include "Program.h"
#include "API.h"
#include "AppMenu.h"

TAppMenu::TAppMenu() : TProgram(false)
{
  icon = (unsigned char *)0;
};
void TAppMenu::Start()
{
  selID = 0;
};
void TAppMenu::ReadButtons(byte &Buttons)
{
  
  if ((Buttons | _BV(1)) == Buttons)
  {
    Buttons &= ~_BV(1);
    selID -= 4;
  }
  if ((Buttons | _BV(5)) == Buttons)
  {
    Buttons &= ~_BV(5);
    selID += 4;
  }
  
  if ((Buttons | _BV(2)) == Buttons)
  {
    Buttons &= ~_BV(2);
    selID -= 1;
  }
  if ((Buttons | _BV(4)) == Buttons)
  {
    Buttons &= ~_BV(4);
    selID += 1;
  }
  
  if ((Buttons | _BV(3)) == Buttons)
  {
    Buttons &= ~_BV(3);
    
    int a = 0;
    for (int i = 0; i < API->Programs->Count(); i++)
    {
      if (a == selID)
      {
        API->RunProgram(i);
      }
      
      if (((TProgram *)API->Programs->GetItem(i))->Visible)
        a++;
    }
  }
    
};
void TAppMenu::Paint(LCD *Canvas)
{
  int a = 0;
  
  for (int i = 0; i < API->Programs->Count(); i++)
  {
    if (((TProgram *)API->Programs->GetItem(i))->Visible)
    {
      Canvas->drawBitmapPGM((a % 4) * 21 + 2,int(a / 4) * 16 + 2,17,12,((TProgram *)API->Programs->GetItem(i))->icon);
      a++;
    }
  }
  
  Canvas->drawRect((selID % 4) * 21,int(selID / 4) * 16,(selID % 4) * 21 + 20,int(selID / 4) * 16 + 15);
};
