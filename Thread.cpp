#include "Thread.h"


void Thread::Sleep(unsigned long ms)
{
  remainingTime = ms;
}

void Thread::remainingSleepTime()
{
  return remainingTime;
}

bool Thread::isSleeping()
{
  return threadState == Thread::SLEEPING;
}
