#ifndef TESTTHREAD_H
#define TESTTHREAD_H

#include "Thread.h"
#include <Arduino.h>



class TestThread : public Thread
{
  public:
    TestThread(char * _name)
    {
      name = _name;
    }
    void Run()
    {
      #ifdef DEBUG
      Serial.print(F("Running test thread: "));
      Serial.println(name);
      #endif
    }
    void Initialize()
    {

    }
};
#endif
