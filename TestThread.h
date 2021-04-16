#ifndef TESTTHREAD_H
#define TESTTHREAD_H

#include "Thread.h"
#include <Arduino.h>



class TestThread : public Thread
{
  public:
    unsigned long sleepEndTime;
    void Run()
    {
      //check if serial communication is ready
      if(Serial)
      {
        //output a message
        Serial.print(F("Running test thread: "));
      }
    }
    void Initialize()
    {

    }
};
#endif
