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
    The inputID specifies which Hardware Button(s) this clickable corresponds to.
    (Note: multiple buttons can have the same ID)
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
    TODO: document args
  */
  Clickable(uint8_t _inputID, void (* _OnClick)()) : inputID(_inputID), OnClick(_OnClick), state(false)
  {

  }
};
#endif
