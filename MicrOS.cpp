#include "MicrOS.h"


/*
  default constructor for the OS
  @param _displayPtr: a pointer to the display
*/
MicrOS::MicrOS(U8G2 * _displayPtr)
{
  //create a new InputManager and WindowManager based on the given arguments
  windowManagerPtr = new WindowManager(_displayPtr);
  inputManagerPtr = new InputManager(windowManagerPtr);
}

//destructor of the default constructor
MicrOS::~MicrOS()
{
  delete inputManagerPtr;
  delete windowManagerPtr;
}

//function starting the OS
void MicrOS::Start()
{
  //start the OS by adding the WindowManager to the running Threads
  AddThread(windowManagerPtr);
}

//run function of the OS, this will run all active threads
void MicrOS::Run()
{
  //run each thread of the thread list
  Thread** threadPtr = threads.getFirstPtr();
  while (threadPtr != nullptr)
  {
    if(!(*threadPtr)->isSleeping())
    {
      (*threadPtr)->Run();
    }
    else
    {
      UpdateSleep((*threadPtr));
    }
    threadPtr = threads.getNextPtr();
  }
}

/*
  function adding the given thread to the list of active threads
  @param threadPtr: pointer to the thread which should be added
  @return: 0 if added successfully,
          -1 if the thread is already inside the list
*/
int MicrOS::AddThread(Thread * threadPtr)
{
  //check if the thread is already inside the list
  if(threads.contains(threadPtr))
  {
    //this thread already is registerad
    return -1;
  }

  MicrOS::threads.add(threadPtr);

  //initialize thread
  threadPtr->Initialize();
  return 0;
}

/*
  function removing the given thread from the list of active threads
  @param threadPtr: pointer to the thread which should be removed
  @return: 0 if removed successfully
          -1 if the element was not found

*/
int MicrOS::RemoveThread(Thread * threadPtr)
{
    //check if the element was found
    if(!threads.contains(threadPtr))
    {
        //element not found
        return -1;
    }
    //element was found
    //delete it from the list
    threads.remove(threadPtr);
    return 0;
}

/*
  function updating the sleep of the given thread if sleeping
*/
void MicrOS::UpdateSleep(Thread* threadPtr)
{
  if(threadPtr->remainingSleepTime() <= 0)
  {
    //wake the tread up from sleep
    threadPtr->Continue();
  }
}

WindowManager * MicrOS::GetWindowManagerPtr()
{
  //return the pointer to the window manager of this OS
  return windowManagerPtr;
}

InputManager * MicrOS::GetInputManagerPtr()
{
  //return the pointer to the input manager of this OS
  return inputManagerPtr;
}
