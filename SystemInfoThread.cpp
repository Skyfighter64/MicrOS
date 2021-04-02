#include "SystemInfoThread.h"


#ifdef __arm__
// should use uinstd.h to define sbrk but Due causes a conflict
extern "C" char* sbrk(int incr);
#else  // __ARM__
extern char *__brkval;
#endif  // __arm__


SystemInfoThread::SystemInfoThread()
{
  name = "SystemInfo";
}



int SystemInfoThread::GetFreeMemory()
{
  char top;
#ifdef __arm__
  return &top - reinterpret_cast<char*>(sbrk(0));
#elif defined(CORE_TEENSY) || (ARDUINO > 103 && ARDUINO != 151)
  return &top - __brkval;
#else  // __arm__
  return __brkval ? &top - __brkval : &top - __malloc_heap_start;
#endif  // __arm__
}



unsigned long SystemInfoThread::GetCycleTime()
{
    return cycleTime;
}

float SystemInfoThread::GetCycleFrequency()
{
    return 1000000.0/cycleTime;
}

void SystemInfoThread::Initialize()
{
    startTime = micros();
}

void SystemInfoThread::Run()
{
    //measure the time of the last cycle
    cycleTime = micros() - startTime;
    //start measuring the next cycle
    startTime = micros();
}
