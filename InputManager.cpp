#include "InputManager.h"


void InputManager::ClickEvent(uint8_t _ID)
{
  //get the clickables of the currently active window
  List<Clickable *> * clickables = &windowManagerPtr->GetActiveWindow()->clickables;

  #ifdef DEBUG
  Serial.print(F("InputManager: Clicked: "));
  Serial.println(_ID );
  #endif

  //loop trough all clickables and execute OnClick of the ones with
  // a matching ID
  Clickable ** iterator = clickables->getFirstPtr();
  while(iterator != NULL)
  {
    if((*iterator)->ID == _ID && (*iterator)->OnClick != NULL)
    {
      (*iterator)->OnClick();
    }
    iterator = clickables->getNextPtr();

  }
}


void InputManager::SetState(uint8_t _ID, bool _state )
{
  //get the clickables of the currently active window
  List<Clickable *> * clickables = &windowManagerPtr->GetActiveWindow()->clickables;

  //loop trough all clickables and execute OnClick of the ones with
  // a matching ID
  Clickable** iterator = clickables->getFirstPtr();
  while(iterator != NULL)
  {
    if((*iterator)->ID == _ID)
    {
      //set the pressed state depending on the state of the given
      (*iterator)->state = _state;
    }
    iterator = clickables->getNextPtr();
  }
}
