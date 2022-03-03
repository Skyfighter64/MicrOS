#include "WindowManager.h"



WindowManager::WindowManager(U8G2 * _displayPtr) : displayPtr(_displayPtr), activeWindowPtr(nullptr)
{

}

void WindowManager::Initialize()
{
  InitializeDisplay();
}


void WindowManager::Run()
{
  // draw the current window if possible
  DrawWindow();
  // update the display if possible
  UpdateDisplay();

  // limit the refresh rate of the display to boost overall performance
  if(frameDelay > 0)
  {
    Sleep(frameDelay);
  }
}



/**
  function drawing the currently active window if possible
*/
void WindowManager::DrawWindow()
{
  //check if there is an active window to draw
  if(activeWindowPtr == nullptr)
  {
      //there is no window to display
      return;
  }

  //draw the currently active window
  activeWindowPtr->Draw(displayPtr);
}


/**
  function initializing the display
*/
void WindowManager::InitializeDisplay()
{
  //check if a valid display was given
  if (displayPtr == nullptr)
  {
      // no valid display given
      return;
  }


  //initialize the display driver
  displayPtr->begin();
  // set the default font
  displayPtr->setFont(u8g2_font_tinytim_tf);
  // initialize window drawing
  displayPtr->firstPage();
}


/**
  function updating the display using the driver if possible
*/
void WindowManager::UpdateDisplay()
{
  //check if a valid display to draw to
  if (displayPtr == nullptr)
  {
      // no valid display given
      return;
  }

  // draw one chunk of the image on the screen
  if(!displayPtr->nextPage())
  {
    // the end of the display was reached
    // return to the top
    displayPtr->firstPage();
  }
}


void WindowManager::SetActiveWindow(Window * windowPtr)
{
  activeWindowPtr = windowPtr;
}
Window * WindowManager::GetActiveWindow()
{
  return activeWindowPtr;
}
