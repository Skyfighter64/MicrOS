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
  //check if ther is data to read from the sensor
  if(irlRemote.available())
  {
    //read the latest received value from the sensor
    Nec_data_t  data = irlRemote.read();
    //launch a click event for the received command
    LaunchClickEvent(data.command);
    //set the state for this command if needed
    SetPressedState(data);
  }
  else
  {
    //no command received
    //check the time to the last receive event
    if(CheckTimeOut())
    {
      //the last IR signal was too long ago
      ResetPressedState();
      //reset the last command
      lastCommand = 0x00;
    }
  }
}

void IRNecDriver::LaunchClickEvent(Nec_command_t command)
{
  //check if the inputID is valid
  //this step is unique for this driver to ignore unwanted signals
  //launch a ClickEvent
  inputManagerPtr->ClickEvent(GetID(command));

}

void IRNecDriver::SetPressedState(Nec_data_t &data)
{
  //check if the received data is a repeat signal
  if(data.address == 0xFFFF && data.command == 0x00)
  {
    //repeat signal received!
    //do nothing
    return;
  }

  //check if the signal is the same as before
  if(data.command != lastCommand)
  {
    //reset the state of the previous signal
    inputManagerPtr->SetState(GetID(lastCommand), false);
    //set the state of the new signal
    inputManagerPtr->SetState(GetID(data.command), true);
    lastCommand = data.command;
  }
}

bool IRNecDriver::CheckTimeOut()
{
  //return if the set timeout was exceeded
  return irlRemote.timeout() >= TIME_OUT;
}

void IRNecDriver::ResetPressedState()
{
  //reset the pressed state of the last command
  inputManagerPtr->SetState(GetID(lastCommand), false);
}


uint8_t IRNecDriver::GetID(Nec_command_t command)
{
  //map the IR commands to Input IDs
  switch (command)
   {
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
