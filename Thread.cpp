#include "Thread.h"


void Thread::Pause()
{
  threadState = Thread::PAUSED;
}

void Thread::Continue()
{
  threadState = Thread::ACTIVE;
}

bool Thread::isPaused()
{
  return threadState == Thread::PAUSED;
}
