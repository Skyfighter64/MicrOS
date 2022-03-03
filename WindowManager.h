#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <U8g2lib.h> //display driver
#include "Thread.h"
#include "Window.h"
#include "List.h"

/*
  This thread handles and draws all windows

  It also provides functions to switch the displayed window
  and updates the display using the display driver
*/


class WindowManager : public Thread
{
  public:
    // the delay in ms inbetween each frame drawn to the screen
    // use to limit the framerate and boost overall performance
    /*
      To calculate the frame delay: e.g. desired frame rate = 60 FPS:
      1000 / 60 Hz = 16,6 ms          -> Frame delay should be ~17ms
      Note: This is not accurate if a page buffer is used by u8g2 (delay has to
       be divided by page count additionally)
    */
    unsigned long frameDelay = 10;

    WindowManager( U8G2 * _displayPtr);
    void SetActiveWindow(Window * windowPtr);
    Window * GetActiveWindow();
    int GetActiveWindowIndex();

    //implementing virtual functions of thread class
    void Initialize();
    void Run();
  protected:
    //the display this windowmanager is managing
    U8G2 * displayPtr;

    //the currently active window
    Window* activeWindowPtr;

    void InitializeDisplay();
    void UpdateDisplay();

    void DrawWindow();
};

#endif
