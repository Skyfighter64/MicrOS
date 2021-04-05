#ifndef IRL_REMOTE_DRIVER_H
#define IRL_REMOTE_DRIVER_H


#include "Thread.h"
#include "InputManager.h"
#include <IRLremote.h>
/*
  Driver for IR remotes with NEC encoding using the IRLremote library
  https://github.com/NicoHood/IRLremote

  This driver is interrupt-based, which means an interrupt-pin has
  to be used for the IR-Receiver (Pin 2 or 3 on Arduino Uno/Nano/Pro mini).

  The other pins could also be used, but this would require installation of the
  PinChangeInterrupt library.
  More on that here:
  https://github.com/NicoHood/IRLremote#setup-receiving

  InputIDs used by this driver:
  TODO

  To customize the InputIDs and their corrensponding IR codes,
  edit GetID(...) in IRNecDriver.cpp
*/

/*
  set the pin of the IR receiver
  Note: If you want to use any other pin than pin 2 or 3, you
  have to add the PinChangeInterrupt library as explained above.
*/
#define RECEIVER_PIN 2

class IRNecDriver : public Thread
{
public:
  /*
    default constructor
  */
  IRNecDriver(InputManager * _inputManagerPtr);
  /*
    implement virtual functions of Thread class
  */
  void Initialize();
  void Run();
protected:
  InputManager * inputManagerPtr;
  CNec irlRemote;
  /*
    function reading data from the IR sensor and
    executing a ClickEvent for the received signal if needed
  */
  void ReadIRSensor();
  /*
    function mapping IR signals to Input IDs
    @param command: the command received by the IR Receiver
    @return: the corresponding Input ID or 255 if not set
  */
  uint8_t GetID(Nec_command_t command);
};

#endif
