#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H
#include <Bounce2.h> //for debouncing buttons
#include <Arduino.h>

/*
  function wrapping the Bounce2 Button class and adding a getter for the physical pin number
*/
class PushButton: public Button
{
  public:
    PushButton(uint8_t pin, uint16_t interval_millis ) : Button()
    {
      //initialize the button
        Button::attach(pin, INPUT);
        Button::interval(interval_millis);
    }
    uint8_t get_pin()
    {
      return pin;
    }
};
#endif
