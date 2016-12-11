#include <Arduino.h>
#include "LCD.h"
#include "List.h"
#include "Timer.h"
#include "Program.h"
#include "Sounds.h"

#include "API.h"

//#include "XO.h"
//#include "MusicBox.h"
#include "Lockscreen.h"
#include "AppMenu.h"

#include "flappyBird.h"
#include "Testing.h"
#include "s3DTest.h"
#include "Taras.h"
#include "Race.h"


#define SHOW_FPS


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

byte Buttons,aButtons;

void readButtons();
void readTimers();
void readClock();
void frame();
void showPart(void *);


void setup()
{
  Timers = new TList;
  API = new _API;
  
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
  
  
  
  API->Programs->Add(new TLockScreen());
  API->Programs->Add(new TAppMenu());
  //Programs->Add(new TXO());
  //Programs->Add(new TMusicBox());
  API->Programs->Add(new TFlappyBird());
  API->Programs->Add(new TTaras());
  //API->Programs->Add(new TRace());
  //API->Programs->Add(new TTesting());
  API->Programs->Add(new T3DTest());
  
  
  //TSounds *mSounds = new TSounds(13);
  //TSound *mSound = Sound(melody,durations,8);
  
  //mSounds->Play(mSound);
  
  API->Run();
  
  #ifdef SHOW_FPS
  addTimer(1000,false,resetFPS,0);
  #endif
  addTimer(1,false,showPart,0);
  
  frame(0);
}

void loop()
{
  //showPart(0);
  
  readButtons();
  API->ReadButtons(Buttons);
  readTimers();
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
        Timers->Delete(i);
        delete curTimer;
        i--;
      }
      else
      {
        curTimer->cTime = millis() + curTimer->Interval;
      }
    };
  };
}

#ifdef SHOW_FPS
int backFPS;
int FPS = 0;

void resetFPS(void *Data)
{
  backFPS = FPS;
  FPS = 0;
}
#endif

void frame(void *Data)
{
  Screen->clear();
  
  API->Render(Screen);
  
  #ifdef SHOW_FPS
  FPS++;
  String sFPS = String(backFPS);
  char fps[5];
  sFPS.toCharArray(fps,5);
  Screen->drawText(0,0,fps);
  #endif
}

void showPart(void *)
{
  static int part;
  
  
  Screen->displayPart(part,56);
  
  part += 56;
  if (part >= 504)
  {
    part = 0;
    frame(0);
  };
};
