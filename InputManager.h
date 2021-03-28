#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <Arduino.h> //serial debugging
#include "List.h"
#include "Clickable.h"
#include "WindowManager.h"
#include "UIButton.h"


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
  void ClickEvent(uint8_t _ID);


  /*
    function getting called by the hardware drivers to update the state
    of the hardware.
    @param _ID: The ID of the clicked Button
    @param _state: the pressed state of the button
      All UIButtons of the currently active window will be updated to
      the given state.
  */
  void SetState(uint8_t _ID, bool _state);

private:
  // pointer to the windowManager of the OS to get
  // the clickables of the active window
  WindowManager * windowManagerPtr;
};

#endif
