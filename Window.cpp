#include "Window.h"


Window::Window(List<Clickable*>& _clickables, List<UIElement*>& _uiElements) : clickables(_clickables), uiElements(_uiElements)
{

}

void Window::Draw(U8G2 * displayPtr)
{

  /*
    TODO: add the position of this window to all UI elements and buttons for multi window support
  */

  /*
    Draw all UI elements
  */
  UIElement ** elementPtr = uiElements.getFirstPtr();
  while(elementPtr != nullptr)
  {
      (*elementPtr)->Draw(displayPtr);
      elementPtr = uiElements.getNextPtr();
  }
}
