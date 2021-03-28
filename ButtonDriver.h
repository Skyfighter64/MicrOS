#ifndef BUTTON_DRIVER_H
#define BUTTON_DRIVER_H

#include <Bounce2.h>
#include <Arduino.h> //serial debugging
#include "Thread.h"
#include "InputManager.h"
#include "List.h"
#include "PushButton.h"

/*
  A driver for standard buttons connected to the digital pins of
  the microcontroller. Includes software debouncing.

  Note: pinMode(..., INPUT) gets set automatically (by Bounce2).

  Used IDs:
  The IDs for the buttons are the same as the number of the pins at which they
  are connected to the microcontroller.

  Therefore, this class may use all IDs from 0 up to the highest digital
  pin number (e.g. 13 for Arduino Uno/Nano/Pro mini).
  Which numbers are actually used depends on the _pins array given to the
  constructor.

  This behaviour can be changed by editing ButtonDriver::GetPin() in ButtonDriver.cpp

*/



class ButtonDriver : public Thread
{
public:
  /*
    Default constructor
    @param _inputManager: the inputManager of the OS
    @pararm _pins: an array containing the numbers of the pins at which
      the buttons are connected to the microcontroller.
    @param _pins_length: the length of the _pins array

    TODO: maybe its better to take an OS pointer as arg
  */
  ButtonDriver(InputManager * _inputManagerPtr, uint8_t * _pins, uint8_t _pins_length);

  //implementing virtual functions of Thread class
  void Initialize();
  void Run();
protected:
  InputManager * inputManagerPtr;
  List<PushButton> pushButtons;
  void UpdateButton(PushButton * buttonPtr);
  uint8_t GetID(PushButton * buttonPtr);
};

#endif
