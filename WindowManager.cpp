#include "WindowManager.h"
#include <Arduino.h>



WindowManager::WindowManager(U8G2 * _displayPtr) : displayPtr(_displayPtr), activeWindowPtr(nullptr)
{

}

void WindowManager::Initialize()
{
  //nothing to do here...
}

/*
    This function crashes when called
*/
void WindowManager::Run()
{
  //check if there are any windows
  if(activeWindowPtr == nullptr)
  {
    #ifdef DEBUG
      Serial.println("No Window to display");
      #endif
      return;
  }

  //draw the currently active window
  activeWindowPtr->Draw(displayPtr);
  #ifdef DEBUG
  Serial.println("Drawing windows...");
  #endif
}


void WindowManager::SetActiveWindow(Window * windowPtr)
{
  activeWindowPtr = windowPtr;
}
Window * WindowManager::GetActiveWindow()
{
  return activeWindowPtr;
}
