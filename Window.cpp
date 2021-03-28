#include "Window.h"


Window::Window(List<Clickable*>& _clickables, List<UIElement*>& _uiElements) : clickables(_clickables), uiElements(_uiElements)
{

}

void Window::Draw(U8G2 * display)
{

  /*
    TODO: add the position of this window to all UI elements and buttons for multi window support
  */

  /*
    Draw all UI elements
  */
  UIElement ** element = uiElements.getFirstPtr();
  while(element != nullptr)
  {
      (*element)->Draw(display);
      element = uiElements.getNextPtr();
  }
}
