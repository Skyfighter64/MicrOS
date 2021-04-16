#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <U8g2lib.h> //display driver
#include "Thread.h"
#include "Window.h"
#include "List.h"

/*
  This thread handles and draws all windows
  and provides functions to switch the displayed window
*/


class WindowManager : public Thread
{
  public:
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
};

#endif
