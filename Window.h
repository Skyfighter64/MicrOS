#ifndef WINDOW_H
#define WINDOW_H

#include <Arduino.h>
#include <U8g2lib.h> //display API
#include "Clickable.h"
#include "UIElement.h"
#include "List.h"


/*
  Class representing an UI Window
*/

class Window : public UIElement
{
public:
  /*
    UI Elements of this window.
    Buttons are seperated to save on performance
  */
  List<Clickable*> clickables;
  List<UIElement*> uiElements;
  void Draw(U8G2 * display);

  Window(List<Clickable*>& _clickables, List<UIElement*>& _uiElements);

};

#endif
