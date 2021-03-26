#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <Arduino.h>
#include "Thread.h"
#include "Window.h"
#include "List.h"
#include <U8g2lib.h>
/*
 this trhead should handle and draw all windows, track which are active
 and have functions to switch the displayed window

 TODO: also add a window which combines multiple windows
*/


class WindowManager : public Thread
{
  public:
    WindowManager( U8G2 * _display);
    void SetActiveWindow(Window * window);
    Window * GetActiveWindow();
    int GetActiveWindowIndex();

    //implementing virtual functions of thread class
    void Initialize();
    void Run();
  protected:
    //the display this windowmanager is managing
    U8G2 * display;

    //the currently active window
    Window* activeWindow;
};

#endif
