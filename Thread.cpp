#include "Thread.h"


void Thread::Sleep(unsigned long ms)
{
  remainingTime = ms;
}

bool Thread::isSleeping()
{
  return threadState == Thread::SLEEPING;
}
