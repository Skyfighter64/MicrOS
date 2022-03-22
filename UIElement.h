#ifndef UIELEMENT_H
#define UIELEMENT_H

#include "Vector2D.h"
#include <U8g2lib.h> //display API


/**
  The base class for everything drawn to the display
  eg. Buttons, TextBoxes, ...

  Contains basic properties such as position and size of the UI Element
  and a Draw() function which implements the drawing to the display of
  this element using the U8G2 Display driver
*/

class UIElement
{
public:
  //position of this UI element on the screen
  Vector2D position;
  // size of this UI element in pixel
  Vector2D size;
  //flag indicating if this UI element should be shown on the screen
  bool visible;
  //constructors
  UIElement();
  UIElement(Vector2D _position, Vector2D _size);
  //virtual function for drawing the UI Element
  virtual void Draw(U8G2 * displayPtr) = 0;
};

#endif
