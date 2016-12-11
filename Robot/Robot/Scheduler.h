#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <Arduino.h>
#define MAX_TASKS 20

class Scheduler
{
private:
  struct Task
  {
    unsigned long time;
    unsigned long interval;
    void (*callback)(unsigned int);
    bool repeat;
  };
  
  Task tasks[MAX_TASKS];
public:
  void post(unsigned int, void (*)(unsigned int), bool repeat = false);
  void tick();
};

#endif
