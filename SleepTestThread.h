#ifndef SLEEP_TEST_THREAD_H
#define SLEEP_TEST_THREAD_H

#include "Thread.h"
#include <Arduino.h>

#define SLEEP_TIME 500 //in ms

/*
  Thread for measuring the acuraccy of thread sleeping
*/

class SleepTestThread : public Thread
{
public:
  void Initialize()
  {
    pinMode(LED_BUILTIN, OUTPUT);
  }
  void Run()
  {
    sleepDelta = millis() - sleepEndTime;
    //blink the builtin led
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    //sleep this thread for SLEEP_TIME
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
