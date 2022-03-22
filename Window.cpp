#include "Window.h"


Window::Window() : clickables(List<Clickable*>()), uiElements(List<UIElement*>())
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

void Window::AddUIElement(UIElement &element)
{
  uiElements.add(&element);
}

void Window::AddClickable(Clickable &clickable)
{
  clickables.add(&clickable);
}
