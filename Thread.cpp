#include "Thread.h"


void Thread::Sleep(unsigned long ms)
{
  sleepEndTime = millis() + ms;
}

unsigned long Thread::remainingSleepTime()
{
  return  isSleeping ? sleepEndTime - millis() : 0;
}

bool Thread::isSleeping()
{
  return threadState == Thread::SLEEPING;
}

void Thread::Continue()
{
  threadState = Thread::ACTIVE;
  sleepEndTime = 0;
}
