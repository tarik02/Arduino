#include "Program.h"
#include "API.h"
#include "Testing.h"
#include "Timer.h"


void TTestingTimer(void *Data)
{
  //((TTesting *)Data)->rot += 0.08;
  //((TTesting *)Data)->ballX = cos(((TTesting *)Data)->rot) * 15;
  //((TTesting *)Data)->ballY = sin(((TTesting *)Data)->rot) * 15;
  
};

TTesting::TTesting() : TProgram(true)
{
  icon = (unsigned char *)TestingIcon;
  
  //addTimer(25,false,TTestingTimer,this);
  //gr = 0;
  //rot = 0;
  Sounds = new TSounds(7);
  Sound = ::Sound(melody,tempo,sizeof(melody) / sizeof(int));
};
void TTesting::Start()
{
  Sounds->Play(Sound);
};
void TTesting::ReadButtons(byte &Buttons)
{
  if ((Buttons | _BV(3)) == Buttons)
  {
    Buttons &= ~_BV(3);
    //Res = cos(PI * 120 / 180.0);
  }
};
void TTesting::Paint(LCD *Canvas)
{
  /*
  Canvas->drawText(2,12,"1");
  Canvas->drawText(11,12,"2");
  Canvas->drawText(20,12,"3");
  
  Canvas->drawText(2,21,"4");
  Canvas->drawText(11,21,"5");
  Canvas->drawText(20,21,"6");
  
  Canvas->drawText(2,30,"7");
  Canvas->drawText(11,30,"8");
  Canvas->drawText(20,30,"9");
  
  Canvas->drawText(2,39," ");
  Canvas->drawText(11,39,"0");
  Canvas->drawText(20,39,".");
  
  Canvas->drawRect(0,0,83,10);
  //String sRes = String(float(Res));
  char cRes[10];
  //sRes.toCharArray(cRes,10);
  dtostrf(Res,10,10,cRes);
  Canvas->drawText(2,2,cRes);
  */
  //Canvas->drawFillRect(42 + (ballX - 2),24 + (ballY - 2),42 + (ballX + 2),24 + (ballY + 2));
};
