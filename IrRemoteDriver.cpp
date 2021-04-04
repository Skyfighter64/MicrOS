#include "IrRemoteDriver.h"

IrRemoteDriver::IrRemoteDriver(InputManager * _inputManagerPtr) : inputManagerPtr(_inputManagerPtr)
{

}

void IrRemoteDriver::Initialize()
{
  //initialize the ir library
  irmp_init();
}

void IrRemoteDriver::Run()
{
  ReceiveData();
}

/*
  function checking for IR signals
*/
void IrRemoteDriver::ReceiveData()
{
  //check if an IR signal was received
  if(irmp_get_data(&irData))
  {
    //execute a clickEvent for the pressed button
    inputManagerPtr->ClickEvent(GetID(irData.command));
  }
}

/*
  function mapping a selected range of IR commands to
  InputIDs

  Change the content of this function if you want to use a different remote
  or different InputIDs

  @param command: the IR command value to get the InputID for
  @return: the InputID for the given command. Default: 255 (for unmapped commands)
*/
uint8_t IrRemoteDriver::GetID(uint16_t command)
{
  switch (command)
  {
    case /* up */ 0x18:
      return 2;
    case /* down */ 0x52:
      return 6;
    case /* left */ 0x08:
      return 3;
    case /* right */ 0x5A:
      return 5;
    default:
      return 255;
  }
}
