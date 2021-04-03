#include "ButtonDriver.h"


ButtonDriver::ButtonDriver(InputManager * _inputManagerPtr, uint8_t * _pins, uint8_t _pins_length) : inputManagerPtr(_inputManagerPtr)
{
  //initialize the list
  pushButtons = List<PushButton>();
  for(uint8_t i = 0; i < _pins_length; i++)
  {
      //generate a PushButton object for every given pin and add it to the list
      pushButtons.add(PushButton(_pins[i], /* update interval */ 25));
  }
}


/*
  this function is called once when the driver gets initialized
*/
void ButtonDriver::Initialize()
{
  //nothing to be done here...
}


/*
  this function is called every OS-Cycle as long as this Thread is active
*/
void ButtonDriver::Run()
{
  //loop trough all buttons
  PushButton * iteratorPtr = pushButtons.getFirstPtr();
  while(iteratorPtr != nullptr)
  {
    UpdateButton(iteratorPtr);
    iteratorPtr = pushButtons.getNextPtr();
  }
}


/*
  function updating the state of the given button
*/
void ButtonDriver::UpdateButton(PushButton * buttonPtr)
{
  #ifdef DEBUG
  Serial.print("Updated button ");
  Serial.println(buttonPtr->get_pin());
  #endif
  //read in the state of the physical button
  buttonPtr->update();
  //update the state of the button
  inputManagerPtr->SetState(GetID(buttonPtr), buttonPtr->isPressed());
  //execute onClick events if the button was released
  if(buttonPtr->fell())
  {
    #ifdef DEBUG
    Serial.print("-- Clicked button ");
    Serial.println(buttonPtr->get_pin());
    #endif
    inputManagerPtr->ClickEvent(GetID(buttonPtr));
  }
}


/*
  Function returning the ID for the given button
*/
uint8_t ButtonDriver::GetID(PushButton * buttonPtr)
{
  /*
    edit this function if you want to change the
    IDs used by this driver
  */
  return buttonPtr->get_pin();
}
