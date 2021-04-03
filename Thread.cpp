#include "Thread.h"


void Thread::Sleep(unsigned long ms)
{
  sleepEndTime = millis() + ms;
  threadState = Thread::SLEEPING;
}

unsigned long Thread::remainingSleepTime()
{
  if(isSleeping())
  {
    return  sleepEndTime > millis() ? sleepEndTime - millis() : 0;
  }
  return 0;
}

bool Thread::isSleeping()
{
  return threadState == Thread::SLEEPING;
}

void Thread::Continue()
{
  threadState = Thread::ACTIVE;
  //run the thread
  Run();
}
