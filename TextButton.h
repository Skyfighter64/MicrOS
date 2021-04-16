#ifndef TEXTBUTTON_H
#define TEXTBUTTON_H

#include <Arduino.h>
#include <U8g2lib.h> //display API

#include "UIButton.h"
#include "Vector2D.h"
#include "TextBox.h"

/*
  class representing a button with text
*/

class TextButton : public UIButton
{
  public:
    //textBox of the Button
    TextBox textBox;

    TextButton(Vector2D _position, char * _text, uint8_t _inputID, void (* _OnClick)());
    TextButton(Vector2D _position, char * _text, uint8_t _inputID, const uint8_t * _font, void (* _OnClick)());
    TextButton(Vector2D _position, Vector2D _size, char * _text, uint8_t _inputID, void (* _OnClick)());
    TextButton(Vector2D _position, Vector2D _size, char * _text, uint8_t _inputID, const uint8_t * _font, void (* _OnClick)());

    void Draw(U8G2 * display);
};
#endif
