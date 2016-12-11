#include "LCD.h"
#include "List.h"
#include "Timer.h"
#include "Program.h"
#include "Sounds.h"

#include "XO.h"
#include "MusicBox.h"
#include "flappyBird.h"

#define BUTTON1 1
#define BUTTON2 2
#define BUTTON3 3
#define BUTTON4 4
#define BUTTON5 5
#define BUTTON6 6

#define S_RST 12
#define S_CE  11
#define S_DC  10
#define S_DIN  9
#define S_CLK  8

LCD *Screen;

typedef enum {sLock,sHome,sProgram}TScreen;

TScreen curScreen = sLock;
byte Buttons,aButtons;

void readButtons();
void readTimers();
void readClock();
void frame();

uint64_t Time;
int64_t TimeOffset = 0;


TProgram *cProgram;

int melody[] = {NOTE_C4,NOTE_G3,NOTE_G3,NOTE_A3,NOTE_G3,0,NOTE_B3,NOTE_C4};
int durations[] = {4,8,8,4,4,4,4,4};

//TSounds *mSounds;
//TSound *mSound;

void setup()
{
  randomSeed(analogRead(0));
  
  pinMode(BUTTON1,INPUT);
  pinMode(BUTTON2,INPUT);
  pinMode(BUTTON3,INPUT);
  pinMode(BUTTON4,INPUT);
  pinMode(BUTTON5,INPUT);
  pinMode(BUTTON6,INPUT);
  pinMode(13,OUTPUT);
  
  Screen = new LCD(S_RST,S_CE,S_DC,S_DIN,S_CLK);
  Screen->clear();
  
  Timers = new TList;
  
  Programs->Add(new TXO());
  Programs->Add(new TMusicBox());
  Programs->Add(new TFlappyBird());
  
  //TSounds *mSounds = new TSounds(13);
  //TSound *mSound = Sound(melody,durations,8);
  
  //mSounds->Play(mSound);
}
void loop()
{
  /*
    Screen->clear();
  
  switch (curScreen)
  {
    case sLock:
    {
      String time = ((Time / 60 / 60 % 24 < 10) ? "0" + String(int(Time / 60 / 60 % 24)) : String(int(Time / 60 / 60 % 24))) + ":" + ((Time / 60 % 60 < 10) ? "0" + String(int(Time / 60 % 60)) : String(int(Time / 60 % 60))) + ":";
      char timeC[7];
      time.toCharArray(timeC,7);
      Screen->drawText(0,6,timeC,true);
      
      String time2 = ((Time % 60 < 10) ? "0" + String(int(Time % 60)) : String(int(Time % 60)));
      char timeC2[3];
      time2.toCharArray(timeC2,3);
      
      Screen->drawTextSize(36,0,timeC2,2,true);
      Screen->drawHLine(0,17,84);
      Screen->drawVLine(61,0,17);
      Screen->drawText(9,19,"< to unlock");
      
      
      if (((Buttons | _BV(2)) == Buttons) && ((Buttons | _BV(6)) == Buttons))
      {
        TimeOffset -= 1;
      }
      else if (((Buttons | _BV(4)) == Buttons) && ((Buttons | _BV(6)) == Buttons))
      {
        TimeOffset += 1;
      }
      else if (((Buttons | _BV(2)) == Buttons) && ((Buttons | _BV(3)) == Buttons))
      {
        TimeOffset -= 60;
      }
      else if (((Buttons | _BV(4)) == Buttons) && ((Buttons | _BV(3)) == Buttons))
      {
        TimeOffset += 60;
      }
      else if (((Buttons | _BV(2)) == Buttons) && ((Buttons | _BV(5)) == Buttons))
      {
        TimeOffset -= 3600;
      }
      else if (((Buttons | _BV(4)) == Buttons) && ((Buttons | _BV(5)) == Buttons))
      {
        TimeOffset += 3600;
      }
      else if ((Buttons | _BV(2)) == Buttons)
      {
        curScreen = sHome;
      };
    }
    break;
    case sHome:
    static int selID;
    
    if (selID < 0)
      selID = 12 - abs(selID);
    if (selID > 11)
      selID = 0;
    
    for (int i = 0; i < Programs->Count(); i++)
    {
      Screen->drawBitmapPGM((i % 4) * 21 + 2,int(i / 4) * 16 + 2,17,12,((TProgram *)Programs->GetItem(i))->icon);
    }
    
    Screen->drawRect((selID % 4) * 21,int(selID / 4) * 16,(selID % 4) * 21 + 20,int(selID / 4) * 16 + 15);
    //Screen->drawBitmapPGM(2,2,17,12,icon);
    
    if ((Buttons | _BV(1)) == Buttons)
    {
      Buttons &= ~_BV(1);
      selID -= 4;
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
    if ((Buttons | _BV(5)) == Buttons)
    {
      Buttons &= ~_BV(5);
      selID += 4;
    }
    if ((Buttons | _BV(6)) == Buttons)
    {
      Buttons &= ~_BV(6);
      curScreen = sLock;
    }
    if ((Buttons | _BV(3)) == Buttons)
    {
      Buttons &= ~_BV(3);
      if (selID <= Programs->Count())
      {
        curScreen = sProgram;
        cProgram = (TProgram *)Programs->GetItem(selID);
        cProgram->Start();
      }
    }
    break;
    case sProgram:
    cProgram->ReadButtons(Buttons);
    cProgram->Paint(Screen);
    
    if ((Buttons | _BV(6)) == Buttons)
    {
      Buttons &= ~_BV(6);
      curScreen = sLock;
    }
    break;
  };
  
  Screen->display();
  */
  addTimer(10,false,frame,0);
  readButtons();
  readTimers();
  readClock();
}


void readButtons()
{
  for (int i = 1; i <= 6; i++)
  {
    if (digitalRead(i) == HIGH)
    {
      if ((aButtons | _BV(i)) != aButtons)
        Buttons |= _BV(i);
      aButtons |= _BV(i);
    }
    else
    {
      if ((aButtons & ~_BV(i)) != aButtons)
        Buttons &= ~_BV(i);
      aButtons &= ~_BV(i);
    }
  }
}
void readTimers()
{
  TTimer *curTimer;
  for (int i = 0; i < Timers->Count(); i++)
  {
    curTimer = (TTimer *)Timers->GetItem(i);
    
    if (millis() >= curTimer->cTime)
    {
      if (curTimer->OnTimer)
        curTimer->OnTimer(curTimer->Data);
      
      if (curTimer->workOnce)
      {
        delete curTimer;
        Timers->Delete(i);
        
        return;
      }
      else
      {
      curTimer->cTime = millis() + curTimer->Interval;
      }
    };
  };
}

void readClock()
{
  Time = millis() / 1000 + TimeOffset;
}

void frame(void *Data)
{
  Screen->clear();
  
  switch (curScreen)
  {
    case sLock:
    {
      String time = ((Time / 60 / 60 % 24 < 10) ? "0" + String(int(Time / 60 / 60 % 24)) : String(int(Time / 60 / 60 % 24))) + ":" + ((Time / 60 % 60 < 10) ? "0" + String(int(Time / 60 % 60)) : String(int(Time / 60 % 60))) + ":";
      char timeC[7];
      time.toCharArray(timeC,7);
      Screen->drawText(0,6,timeC,true);
      
      String time2 = ((Time % 60 < 10) ? "0" + String(int(Time % 60)) : String(int(Time % 60)));
      char timeC2[3];
      time2.toCharArray(timeC2,3);
      
      Screen->drawTextSize(36,0,timeC2,2,true);
      Screen->drawHLine(0,17,84);
      Screen->drawVLine(61,0,17);
      Screen->drawText(9,19,"< to unlock");
      
      
      if (((Buttons | _BV(2)) == Buttons) && ((Buttons | _BV(6)) == Buttons))
      {
        TimeOffset -= 1;
      }
      else if (((Buttons | _BV(4)) == Buttons) && ((Buttons | _BV(6)) == Buttons))
      {
        TimeOffset += 1;
      }
      else if (((Buttons | _BV(2)) == Buttons) && ((Buttons | _BV(3)) == Buttons))
      {
        TimeOffset -= 60;
      }
      else if (((Buttons | _BV(4)) == Buttons) && ((Buttons | _BV(3)) == Buttons))
      {
        TimeOffset += 60;
      }
      else if (((Buttons | _BV(2)) == Buttons) && ((Buttons | _BV(5)) == Buttons))
      {
        TimeOffset -= 3600;
      }
      else if (((Buttons | _BV(4)) == Buttons) && ((Buttons | _BV(5)) == Buttons))
      {
        TimeOffset += 3600;
      }
      else if ((Buttons | _BV(2)) == Buttons)
      {
        curScreen = sHome;
      };
    }
    break;
    case sHome:
    static int selID;
    
    if (selID < 0)
      selID = 12 - abs(selID);
    if (selID > 11)
      selID = 0;
    
    for (int i = 0; i < Programs->Count(); i++)
    {
      Screen->drawBitmapPGM((i % 4) * 21 + 2,int(i / 4) * 16 + 2,17,12,((TProgram *)Programs->GetItem(i))->icon);
    }
    
    Screen->drawRect((selID % 4) * 21,int(selID / 4) * 16,(selID % 4) * 21 + 20,int(selID / 4) * 16 + 15);
    //Screen->drawBitmapPGM(2,2,17,12,icon);
    
    if ((Buttons | _BV(1)) == Buttons)
    {
      Buttons &= ~_BV(1);
      selID -= 4;
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
    if ((Buttons | _BV(5)) == Buttons)
    {
      Buttons &= ~_BV(5);
      selID += 4;
    }
    if ((Buttons | _BV(6)) == Buttons)
    {
      Buttons &= ~_BV(6);
      curScreen = sLock;
    }
    if ((Buttons | _BV(3)) == Buttons)
    {
      Buttons &= ~_BV(3);
      if (selID <= Programs->Count())
      {
        curScreen = sProgram;
        cProgram = (TProgram *)Programs->GetItem(selID);
        cProgram->Start();
      }
    }
    break;
    case sProgram:
    cProgram->ReadButtons(Buttons);
    cProgram->Paint(Screen);
    
    if ((Buttons | _BV(6)) == Buttons)
    {
      Buttons &= ~_BV(6);
      curScreen = sLock;
    }
    break;
  };
  
  
  Screen->display();
}

