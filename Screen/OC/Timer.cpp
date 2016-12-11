#include "Timer.h"

TList *Timers;

TTimer *addTimer(uint32_t Interval,bool workOnce,TOnTimer OnTimer,void *Data)
{
  TTimer *newTimer = new TTimer;
  newTimer->Interval = Interval;
  newTimer->workOnce = workOnce;
  newTimer->OnTimer = OnTimer;
  newTimer->cTime = millis() + Interval;
  newTimer->Data = Data;
  //Timers->Insert(0,newTimer);
  Timers->Add(newTimer);
  
  return newTimer;
};


