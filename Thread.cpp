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
    #ifdef DEBUG
    Serial.print(name);
    Serial.print(" sleeping for ");
    Serial.println(sleepEndTime - millis());
    #endif
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
  #ifdef DEBUG
  Serial.print(name);
  Serial.println(" stopped sleeping");
  #endif
  threadState = Thread::ACTIVE;
  sleepEndTime = 0;
}
