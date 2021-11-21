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

  The other pins could also be used, but this requires installation of the
  PinChangeInterrupt library.
  More on that here:
  https://github.com/NicoHood/IRLremote#setup-receiving

  InputIDs used by this driver:
  +------------------+------------+----------+
  | IR Remote Button | IR Command | Input ID |
  +------------------+------------+----------+
  | up               | 0x18       |        4 |
  | down             | 0x52       |        6 |
  | left             | 0x8        |        3 |
  | right            | 0x5A       |        5 |
  | ok               | 0x1C       |       27 |
  | *                | 0x16       |       28 |
  | #                | 0xD        |       29 |
  | 0                | 0x19       |       30 |
  | 1                | 0x45       |       31 |
  | 2                | 0x46       |       32 |
  | 3                | 0x47       |       33 |
  | 4                | 0x44       |       34 |
  | 5                | 0x40       |       35 |
  | 6                | 0x43       |       36 |
  | 7                | 0x7        |       37 |
  | 8                | 0x15       |       38 |
  | 9                | 0x9        |       39 |
  +------------------+------------+----------+

  To customize the InputIDs and their corrensponding IR commands,
  edit GetID(...) in IRNecDriver.cpp

*/

/*
  The pin at which the IR receiver is connected
  Note: If you want to use any other pin than pin 2 or 3, you
  have to add the PinChangeInterrupt library as explained above.
*/
#define RECEIVER_PIN 2

/*
  Set the reset timeout in us for the ir remote.
  If no IR signal was received for this time or longer,
  the button state of the last pressed button gets reset.

  Default: 108ms (The time in between two repeat signals according to the NEC protocol)
*/
#define TIME_OUT 108000UL



class IRNecDriver : public Thread
{
public:
  /*
    default constructor
    @param _inputManagerPtr: the inputManager of the OS, non-null
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
  //save the last command
  Nec_command_t lastCommand;

  /*
    function reading data from the IR sensor and
    executing a ClickEvent for the received signal if needed
  */
  void ReadIRSensor();

  /*
    function executing a ClickEvent for the received signal if needed
  */
  void LaunchClickEvent(Nec_command_t command);

  /*
    functions for tracking when a button of the remote gets pressed and held down
  */
  void SetPressedState(Nec_data_t& data);

  /*
    function returning if the TIME_OUT time was exceeded since the last
    received IR command
    @return: true, if the time since the last ir signal is >= the TIME_OUT value, else false
  */
  bool CheckTimeOut();

  /*
    function resetting the pressed state for the lastCommand
  */
  void ResetPressedState();
  /*
    function mapping IR signals to Input IDs
    @param command: the command received by the IR Receiver
    @return: the corresponding Input ID or 255 if not set
  */
  uint8_t GetID(Nec_command_t command);
};

#endif
