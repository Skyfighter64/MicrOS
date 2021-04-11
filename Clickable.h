#ifndef CLICKABLE_H
#define CLICKABLE_H
#include <Arduino.h>

/*
  base class for all clickable ui elements
*/

class Clickable
{
public:
  /*
    the OnClick function gets executed every time this
    clickable gets clicked
   */
  void (* OnClick)() = 0;

  /*
    The inputID specifies which Hardware (eg. Button(s)) this clickable corresponds to.

    When the InputManager receives a ClickEvent from an input driver with
    an Input ID, it checks all clickables of the currently active window for
    clickables with the same Input ID and executes their OnClick() functions.

    Note:
      - Multiple buttons can have the same Input ID
      - Multiple clickables can have the same Input ID
  */
  uint8_t inputID;

  /*
    a boolean flag saving the current state of the clickable.
    True: clickable is currently pressed
    False: clickable is currently not pressed
  */
  bool state;

  /*
    default constructor
    @param _inputID: The input ID of the hardware input (eg. a physical button)
      to which this clickable should be linked.
    @param (* OnClick)(): A pointer to  function which will be executed, when this
      clickable gets clicked.
  */
  Clickable(uint8_t _inputID, void (* _OnClick)()) : inputID(_inputID), OnClick(_OnClick), state(false)
  {

  }
};
#endif
