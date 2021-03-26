#ifndef MICROS_H
#define MICROS_H

#include "Thread.h"
#include "PushButton.h"
#include "Window.h"
#include "WindowManager.h"
#include "InputManager.h"
#include <U8g2lib.h> // display driver


/*
Micros is the  Operating System

it should have a list with all threads and run them. It also should keep track of thread sleep times
And start/stop threads



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

};

#endif
