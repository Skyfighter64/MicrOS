#ifndef SYSTEM_INFO_THREAD_H
#define SYSTEM_INFO_THREAD_H

#include <Arduino.h>
#include "Thread.h"

/*

  A Thread measuring and providing core system informations
  such as the current Cycle Time, Cycle Frequency and Memory usage.

*/

class SystemInfoThread : public Thread
{
public:

  /*
    function returning the amount of Memory left for dynamic allocation
    Credit to: https://github.com/mpflaga/Arduino-MemoryFree
    More on how it works: https://learn.adafruit.com/memories-of-an-arduino/measuring-free-memory#sram-370031-5
  */
  int GetFreeMemory();
  /*
    function returning the cycle time for the last OS cycle in us
    This may return false information if called within the first cycle
    after waking up from sleep
  */
  unsigned long GetCycleTime();
  /*
    function returning the cycle freqency in Hertz
    This may return false information if called within the first cycle
    after waking up from sleep
  */
  float GetCycleFrequency();

  //override virtual funcitons from Thread.h
  void Initialize();
  void Run();

protected:
  // the time of the last cycle in us
  unsigned long cycleTime;
  //the start time used for measuring the cycle time in us
  unsigned long startTime;

};
#endif
