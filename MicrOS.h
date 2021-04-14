#ifndef MICROS_H
#define MICROS_H

#include "Thread.h"
#include "PushButton.h"
#include "Window.h"
#include "WindowManager.h"
#include "InputManager.h"
#include <U8g2lib.h> // display driver
#include <Arduino.h> // serial debugging

/*

  Micros is a simple operating system designed for Arduino,
  intended for use with small SPI or I2C displays.

  It supports cooperative multitasking and driver-based user-input.

*/


class MicrOS
{
  public:
    // standard constructor
    MicrOS(U8G2 * _display, List<PushButton*> _buttons, List<Window*> _windows);

    MicrOS(WindowManager * _windwoManagerPtr, InputManager * _inputManagerPtr);
    //function starting the OS
    void Start();
    //run function of the OS, this should be the only call inside loop() //TODO: maybe replace with blocking infinite loop and stop() function
    void Run();
    //functions for adding and removing threads
    int AddThread(Thread * threadPtr);
    int RemoveThread(Thread * threadPtr);

    //getter for special threads
    WindowManager * GetWindowManager();
    InputManager * GetInputManager();

  protected:
    //a list of all currently running threads
    List<Thread*> threads;
    //pointer to special threads, null if there are no such threads (typically only before start)
    WindowManager * windowManagerPtr;
    InputManager * inputManagerPtr;

    /*
      function updating the remaining sleep time of the given thread
      and waking it up if necesary
    */
    void UpdateSleep(Thread *);

};

#endif
