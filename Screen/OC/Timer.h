#ifndef _TIMER_
#define _TIMER_
#include "List.h"
#include <Arduino.h>
typedef void (*TOnTimer)(void *Data);

class TTimer
{
  private:
  public:
  TTimer() {  };
  
  uint32_t Interval;
  bool workOnce;
  uint32_t cTime;
  
  TOnTimer OnTimer;
  
  void *Data;
};

TTimer *addTimer(uint32_t Interval,bool workOnce,TOnTimer OnTimer,void *Data = 0);

extern TList *Timers;// = new TList;

#endif
