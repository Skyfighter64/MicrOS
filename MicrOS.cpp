#include "MicrOS.h"



/*
  standard constructor for the OS
  @param _displayPtr: a pointer to the display
*/
MicrOS::MicrOS(U8G2 * _displayPtr)
{
  /*
      TODO: delete
      This constructor does not work currently
      Accessing UIButton::pin in Inputmanager.cpp does not work because the inputmanager
      gets dynamically allocated below and somehow the UIButton::pin returns undefined values
      instead of the pin.

      Maybe the pointer gets out of scope or something like that.
      For now, use the other constructor with globally defined window-, and inputmanager

  */


  //create a new InputManager and WindowManager based on the given arguments
  windowManagerPtr = new WindowManager(_displayPtr);
  inputManagerPtr = new InputManager(windowManagerPtr);
}

//destructor of the default constructor
MicrOS::~MicrOS()
{
  //TODO: check if this is ok with the constructor using predefined (maybe global) pointers
  delete inputManagerPtr;
  delete windowManagerPtr;
}

/*
  constructor for predefined WindowManager and inputManager
*/
MicrOS::MicrOS( WindowManager *_windowManagerPtr, InputManager * _inputManagerPtr) : windowManagerPtr(_windowManagerPtr), inputManagerPtr(_inputManagerPtr)
{

}

//function starting the OS
void MicrOS::Start()
{
  //TODO: maybe add a fancy little boot screen
  #ifdef DEBUG
  Serial.println(F("Starting OS..."));
  #endif
  //start the OS by adding the WindowManager to the running Threads
  AddThread(windowManagerPtr);
  #ifdef DEBUG
  Serial.println(F("Started OS..."));
  delay(1000);
  #endif

}
//run function of the OS, this should be the only call inside loop()
//TODO: maybe replace with blocking infinite loop and stop() function
void MicrOS::Run()
{

  #ifdef DEBUG
  Serial.println(F("os.Run"));
  #endif
  //run each thread of the thread list
  Thread** thread = threads.getFirstPtr();
  while (thread != nullptr)
  {
    if(!(*thread)->isSleeping())
    {
      (*thread)->Run();
      #ifdef DEBUG
      Serial.print(F("Running Thread: "));
      Serial.println((*thread)->name);
      #endif
    }
    else
    {
      UpdateSleep((*thread));
    }
    thread = threads.getNextPtr();
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

  //TODO: this line caused the arduino to freeze / crash when using vectors
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
void MicrOS::UpdateSleep(Thread* thread)
{
  if(thread->remainingSleepTime() <= 0)
  {
    //wake the tread up from sleep
    thread->Continue();
  }
}

WindowManager * MicrOS::GetWindowManagerPtr()
{
  //return the pointer to the window manager of this OS
  //Note: this can be a null pointer if this OS has no WindowManager
  return windowManagerPtr;
}
InputManager * MicrOS::GetInputManagerPtr()
{
  //return the pointer to the input manager of this OS
  //Note: this can be a null pointer if this OS has no InputManager
  return inputManagerPtr;
}
