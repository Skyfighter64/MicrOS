#ifndef MICROS_H
#define MICROS_H

#include "Thread.h"
#include "PushButton.h"
#include "Window.h"
#include "WindowManager.h"
#include "InputManager.h"
#include "List.h"
#include <U8g2lib.h> // display driver

/*

  Micros is a simple operating system designed for Arduino,
  intended for use with small SPI or I2C displays.

  It supports cooperative multitasking and driver-based user-input.

*/


class MicrOS
{
  public:
    // default constructor
    MicrOS(U8G2 * _displayPtr);
    // default destructor
    ~MicrOS();
    //function starting the OS, this should be called only once, e.g. in setup()
    void Start();
    //run function of the OS, this should be the only call inside loop()
    void Run();
    //functions for adding and removing threads
    int AddThread(Thread * threadPtr);
    int RemoveThread(Thread * threadPtr);

    //getter for core OS components
    WindowManager * GetWindowManagerPtr();
    InputManager * GetInputManagerPtr();

  protected:
    //a list of all currently running threads
    List<Thread*> threads;
    //pointer to the window manager thread, null if there are no such threads (typically only before start)
    WindowManager * windowManagerPtr;
    //pointer to the inputManager
    InputManager * inputManagerPtr;

    /*
      function updating the remaining sleep time of the given thread
      and waking it up if necesary
    */
    void UpdateSleep(Thread * threadPtr);

};

#endif
