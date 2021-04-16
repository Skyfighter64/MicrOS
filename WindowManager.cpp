#include "WindowManager.h"



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
      //there is no window to display
      return;
  }

  //draw the currently active window
  activeWindowPtr->Draw(displayPtr);
}


void WindowManager::SetActiveWindow(Window * windowPtr)
{
  activeWindowPtr = windowPtr;
}
Window * WindowManager::GetActiveWindow()
{
  return activeWindowPtr;
}
