#ifndef THREAD_H
#define THREAD_H

#include <Arduino.h>

/*
  Base class for threads running on MicrOS

  How it works:

  A Thread is an object which can run code inside MicrOS.

  Every Thread has an "Initialize()" and a "Run()" function.

  The "Initialize()" function gets executed by MicrOS once when the Thread is
  added (similar to the arduino "start()" function).

    | To add a Thread to MicrOS, call MicrOS::AddThread(...) with a pointer
    | to your thread.

  The "Run()" function is called continuosuly every OS cycle (Similar to
  the arduino "loop()" function).

    | The code inside the "Run()" function of a Thead should be fast and
    | non-blocking.
    | Therefore you should not use "delay(...)" or large loops within "Run()"
    | as it directly impacts OS performance

  If you want to pause a thread for a certain time, you can use Thread::Sleep(...)
  to do so. This will pause the execution of "Run()" for this thread for
  AT LEAST the given amount of time.

  More specifically, the REAL sleep time is:
  - At least the "given sleep time"
  - Less or equal the "given sleep time" + the "OS cycle time"

    | The "OS cycle time" is the time MicrOS needs for one full cycle
    | which consists of:
    |   - Executing "Run()" for all active threads
    |   - Drawing the active window to the display
    |   - Executing everything in the arduino "loop()" function
    |
    | and therefore depends heavily on the Threads running and the
    | performance of the microcontroller.
    |
    | It can be measured using "SystemInfoThread.h"


  Create your own Threads:

  To create threads running your custom code, simply create a class deriving from
  the "Thread" class.

  You will need to implement the virtual functions "Initialize()" and "Run()" within
  your custom thread.

*/

class Thread
{
  public:
    virtual void Initialize() = 0;
    virtual void Run() = 0;
    void Sleep(unsigned long ms);
    bool isSleeping();
    /*
      function returning the remaining sleep time in ms
    */
    unsigned long remainingSleepTime();
    //function waking the thread up from sleep
    void Continue();
    enum State
    {
      ACTIVE = 0,
      SLEEPING = 1
    };

  protected:
    //the time in ms at which the thread finishes sleeping
    unsigned long sleepEndTime;
    //flag indicating the current state of this thread
    State threadState;

};
#endif
