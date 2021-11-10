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
    Serial.println("Received IR Signal");
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
     /* navigation buttons */
    case /* up */ 0x18:
      return 11;
    case /* down */ 0x52:
      return 7;
    case /* left */ 0x08:
      return 12;
    case /* right */ 0x5A:
      return 6;
    case /* OK */ 0x1C:
      return 27;

      /* number block */
    case /* * */ 0x16:
      return 28;
    case /* # */ 0xD:
      return 29;
    case /* 0 */ 0x19:
      return 30;
    case /* 1 */ 0x45:
      return 31;
    case /* 2 */ 0x46:
      return 32;
    case /* 3 */ 0x47:
      return 33;
    case /* 4 */ 0x44:
      return 34;
    case /* 5 */ 0x40:
      return 35;
    case /* 6 */ 0x43:
      return 36;
    case /* 7 */ 0x7:
      return 37;
    case /* 8 */ 0x15:
      return 38;
    case /* 9 */ 0x9:
      return 39;

    default:
      return 255;
  }
}
