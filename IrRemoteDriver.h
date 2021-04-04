#ifndef IR_REMOTE_DRIVER_H
#define IR_REMOTE_DRIVER_H

#include "InputManager.h"

/*
  An input driver for infrared remotes using the IRMP infrared library.
  This requires an IR-Receiver connected to the microcontroller.

  More info's about the IRMP library here: https://github.com/ukw100/IRMP
  Input IDs used for this driver:

  TODO

  To customize the IDs and their corrensponding IR codes,
  edit GetID(...) in IrRemoteDriver.cpp
*/

/*
  The pin at which the IR Receiver is connected
*/
#define IRMP_INPUT_PIN 4



#define IRMP_PROTOCOL_NAMES 1 // Enable protocol number mapping to protocol strings - requires some FLASH.
/*
  import the library and configure it to only use the NEC protocol to save memory
  and performance
*/
//#include <irmpSelectMain15Protocols.h>  // This enables 15 main protocols
#define IRMP_SUPPORT_NEC_PROTOCOL        1 // this enables only one protocol
#include <irmp.c.h>

class IrRemoteDriver : public Thread
{
public:
/*
  default constructor
  @param _inputManager: a pointer to the input manager to which click events
    will be sent
*/
IrRemoteDriver(InputManager * _inputManagerPtr);

/*
  implementing virtual functions from Thread class
*/
void Initialize();
void Run();

protected:
  //keep a pointer to the inputManager
  InputManager * inputManagerPtr;

  //buffer for the received ir data
  IRMP_DATA irData;
  /*
    function mapping an IR code to an input id
    @param command: the received IR command
  */
  uint8_t GetID(uint16_t command);
  void ReceiveData();
};


#endif
