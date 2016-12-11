#include "Scheduler.h"

void Scheduler::post(unsigned int time, void (*callback)(unsigned int), bool repeat)
{
  for (auto i = 0; i < MAX_TASKS; i++)
  {
    if (tasks[i].time == 0)
    {
      tasks[i].time = millis() + time;
      tasks[i].interval = time;
      tasks[i].callback = callback;
      tasks[i].repeat = repeat;
      return;
    }
  }
}

void Scheduler::tick()
{
  for (auto i = 0; i < MAX_TASKS; i++)
  {
    if ((tasks[i].time != 0) && (tasks[i].time < millis()))
    {
      auto diff = millis() - tasks[i].time - 1;
      tasks[i].callback(diff);

      if (tasks[i].repeat)
      {
        tasks[i].time = millis() + tasks[i].interval - diff;
      }
      else
      {
        tasks[i].time = 0;
      }
    }
  }
}

