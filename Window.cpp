#include "Window.h"


Window::Window(List<Clickable*>& _clickables, List<UIElement*>& _uiElements) : clickables(_clickables), uiElements(_uiElements)
{

}

void Window::Draw(U8G2 * displayPtr)
{
  // check if a display is present
  if(displayPtr == nullptr)
  {
    //no display given
    return;
  }
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
