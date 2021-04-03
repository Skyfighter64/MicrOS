#include "WindowManager.h"
#include <Arduino.h>



WindowManager::WindowManager(U8G2 * _display) : display(_display), activeWindow(nullptr)
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
  if( activeWindow == nullptr)
  {
    #ifdef DEBUG
      Serial.println("No Window to display");
      #endif
      return;
  }

  //draw the currently active window
  activeWindow->Draw(display);
  #ifdef DEBUG
  Serial.println("Drawing windows...");
  #endif
}


void WindowManager::SetActiveWindow(Window * window)
{
  activeWindow = window;
}
Window * WindowManager::GetActiveWindow()
{
  return activeWindow;
}
