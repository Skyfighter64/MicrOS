#include "Thread.h"


void Thread::Sleep(unsigned long ms)
{
  sleepEndTime = millis() + ms;
}

void Thread::remainingSleepTime()
{
  return  isSleeping ? sleepEndTime - millis() : 0;
}

bool Thread::isSleeping()
{
  return threadState == Thread::SLEEPING;
}
