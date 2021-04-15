#include "InputManager.h"


void InputManager::ClickEvent(uint8_t _inputID)
{
  //get the clickables of the currently active window
  List<Clickable *> * clickablesPtr = &windowManagerPtr->GetActiveWindow()->clickables;

  #ifdef DEBUG
  Serial.print(F("InputManager: Clicked: "));
  Serial.println(_inputID );
  #endif

  //loop trough all clickables and execute OnClick of the ones with
  // a matching ID
  Clickable ** iterator = clickablesPtr->getFirstPtr();
  while(iterator != nullptr)
  {
    if((*iterator)->inputID == _inputID && (*iterator)->OnClick != nullptr)
    {
      (*iterator)->OnClick();
    }
    iterator = clickablesPtr->getNextPtr();

  }
}


void InputManager::SetState(uint8_t _inputID, bool _state )
{
  //get the clickables of the currently active window
  List<Clickable *> * clickablesPtr = &windowManagerPtr->GetActiveWindow()->clickables;

  //loop trough all clickables and execute OnClick of the ones with
  // a matching ID
  Clickable** iterator = clickablesPtr->getFirstPtr();
  while(iterator != nullptr)
  {
    if((*iterator)->inputID == _inputID)
    {
      //set the pressed state depending on the state of the given
      (*iterator)->state = _state;
    }
    iterator = clickablesPtr->getNextPtr();
  }
}
