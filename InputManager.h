#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <Arduino.h> //for uint8_t
#include "List.h"
#include "Clickable.h"
#include "WindowManager.h"


/*
  A class for managing Inputs from all kinds of input drivers.

  The InputManager is a core part of this operating system. It provides
  a "ClickEvent()" and a "SetState()" function for input drivers to call.

    | Input drivers are threads which can detect hardware inputs.
    | Examples:
    |   ButtonDriver : An input driver which detects inputs of hardware buttons connected
    |      to the pins of the microcontroller
    |   IRNecDriver : An input driver which reads inputs from infrared remotes

  When a driver detects an input (eg. a button press), it calls
  the "InputManager::ClickEvent(...)" function of the Input Manager and
  passes an "Input ID" as an argument.

    | Input IDs are numbers from 0 to 255 which link a hardware click to different
    | OnClick() - functions depending on which Window is shown on the display.
    |
    | They are statically set inside each input driver but can be changed to fit
    | your needs

  The InputManager asks the WindowManager for the currently active window and
  retrieves its clickable objects.

    | Clickables are Objects with an Input ID and a pointer to an OnClick() function.

  It then loops trough all clickables, finds the ones with a matching Input ID
  as the one received by the driver, and executes the "OnClick()" function each of them.



  Wenever a button (etc...) is pressed down or released, the input driver can also call

  "InputManager::SetState(..., true)"
    or
  "InputManager::SetState(..., false)"

  depending on the state of the button.

  The state should be an indicator for if a hardware button is held down.
  Therefore, whenever a hardware button (etc...) is held down,
  the state of ALL CLICKABLES of the active window with the SAME INPUT ID will be
  "true".

  The primary use of the Clickable::state value is highlighting of TextButtons
  in the user interface.


*/
class InputManager
{
public:

  /*
    default constructor
  */
  InputManager(WindowManager * _windowManagerPtr): windowManagerPtr(_windowManagerPtr)
  {

  }
  /*
    function getting called by the hardware drivers whenever the
    hardware gets clicked
    @param _ID: The ID of the clicked Button
        All clickables of the currently active window with this ID
        will be executed
  */
  void ClickEvent(uint8_t _inputID);


  /*
    function getting called by the hardware drivers to update the state
    of the hardware.
    @param _ID: The ID of the clicked Button
    @param _state: the pressed state of the button
      All Clickables of the currently active window will be updated to
      the given state.
  */
  void SetState(uint8_t _inputID, bool _state);

private:
  // pointer to the windowManager of the OS to get
  // the clickables of the active window
  WindowManager * windowManagerPtr;
};

#endif
