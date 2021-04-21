#ifndef TEXTBUTTON_H
#define TEXTBUTTON_H

#include <Arduino.h>
#include <U8g2lib.h> //display API

#include "Clickable.h"
#include "Vector2D.h"
#include "SimpleTextBox.h"

/*
  class representing a button with text
*/

class TextButton : public SimpleTextBox, public Clickable
{
  public:
    TextButton(U8G2 * _displayPtr, Vector2D _position, char * _text, uint8_t _inputID, void (* _OnClick)());
    TextButton(U8G2 * _displayPtr, Vector2D _position, char * _text, uint8_t _inputID, const uint8_t * _font, void (* _OnClick)());

    void Draw(U8G2 * display);
};
#endif
