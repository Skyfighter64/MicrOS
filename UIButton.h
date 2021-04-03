#ifndef UIBUTTON_H
#define UIBUTTON_H

#include <Arduino.h>
#include "UIElement.h"
#include "Clickable.h"


/*
  The base class for all Button Objects
*/
class UIButton : public UIElement, public Clickable
{
  public:
    //default constructor
    UIButton(Vector2D _position, Vector2D _size, uint8_t _inputID, void (* _OnClick)());
};
#endif
