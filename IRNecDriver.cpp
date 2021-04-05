#include "IRNecDriver.h"


IRNecDriver::IRNecDriver(InputManager * _inputManagerPtr) : inputManagerPtr(_inputManagerPtr)
{
  //nothing to do here
}

void IRNecDriver::Initialize()
{
  irlRemote.begin(RECEIVER_PIN);
}

void IRNecDriver::Run()
{
  //read the data from the IR sensor and execute a ClickeEvent if needed
  ReadIRSensor();
}

void IRNecDriver::ReadIRSensor()
{
  //read the latest received value from the sensor
  Nec_data_t  data = irlRemote.read();
  //get the input ID for the received value
  uint8_t inputID = GetID(data.command);

  //check if the inputID is valid
  //this step is unique for this driver to ignore unwanted signals
  if(inputID != 255)
  {
      //launch a ClickEvent
      inputManagerPtr->ClickEvent(inputID);
  }
}

uint8_t IRNecDriver::GetID(Nec_command_t command)
{
  switch (command) {
    case /* up */ 0x18:
      return 4;
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
