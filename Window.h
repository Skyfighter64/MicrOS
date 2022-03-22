#ifndef WINDOW_H
#define WINDOW_H

#include <Arduino.h>
#include <U8g2lib.h> //display API
#include "Clickable.h"
#include "UIElement.h"
#include "List.h"


/*
  Class representing an UI Window

  How it works:

  A window is a container for:

    - UI elements
    - clickables

  Where UI Elements can be anything inheriting from "UIElement".
  Whenever the Window gets drawn by the WindowManager, the "Draw()" function
  of each UIElement of this window gets executed.

  This results in those UIElements being drawn onto the screen.


  Clickables are objects containing an "OnClick()" function and an InputID.

  Whenever a button with the same InputID as a clickable gets pressed, the clickable's
  "OnClick()" function will be automatically executed by the InputManager,
  but ONLY IF the clickable is part of the currently active window.

    | To switch the currently active window, simply call
    | WindowManager::SetActiveWindow(...)

  Therefore, each button can do different things depending on which window gets
  displayed on the screen.
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
  void Draw(U8G2 * displayPtr);
  void AddUIElement(UIElement &element);
  void AddClickable(Clickable &clickable);

  Window();

};

#endif
