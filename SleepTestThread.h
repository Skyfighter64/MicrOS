#ifndef SLEEP_TEST_THREAD_H
#define SLEEP_TEST_THREAD_H

#include "Thread.h"
#include <Arduino.h>

#define SLEEP_TIME 1000

/*
  Thread for measuring the acuraccy of thread sleeping
*/

class SleepTestThread : public Thread
{
public:
  void Initialize()
  {
    //do nothing
  }
  void Run()
  {
    sleepDelta = millis() - sleepEndTime;
    //sleep this thread for 10s
    Sleep(SLEEP_TIME);
  }

/*
  function returning the sleep delta in ms
*/
  unsigned long GetDelta()
  {
    return sleepDelta;
  }
/*
  function returning the sleep delta percentage
*/
  int GetDeltaPercentage()
  {
    return (sleepDelta * 100) / SLEEP_TIME;
  }
protected:
  //the difference betwenn the wanted sleep time and the actual sleep time
  unsigned long sleepDelta;
};
#endif
