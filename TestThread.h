#ifndef TESTTHREAD_H
#define TESTTHREAD_H

#include "Thread.h"
#include <Arduino.h>



class TestThread : public Thread
{
  public:
    int counter
    void Initialize()
    {
      //start serial communication
      Serial.begin(9600);
      //reset the counter
      counter = 0;
    }
    void Run()
    {
      //check if serial communication is ready
      if(Serial)
      {
        counter ++;
        //output a message
        Serial.print(F("Running test thread"));
        Serial.println(counter);
        //wait for 1000ms
        Sleep(1000);
      }
    }

};
#endif
