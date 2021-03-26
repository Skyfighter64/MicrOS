#ifndef UIELEMENT_H
#define UIELEMENT_H

#include "Vector2D.h"
#include <U8g2lib.h> //display API

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
  virtual void Draw(U8G2 * display) = 0;
};

#endif
