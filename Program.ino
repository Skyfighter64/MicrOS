#include <Arduino.h>
#include "MicrOS.h"
#include "SystemInfoThread.h"
#include "ButtonDriver.h"

// add threads for temporary performance measuring
SystemInfoThread infoThread = SystemInfoThread();


void ShowRam()
{
    Serial.print("Ram left: ");
    Serial.print(infoThread.GetFreeMemory());
    Serial.println("b");

}



Clickable showRamButton(6, &ShowRam);
List<Clickable*> windowButtons(1, (Clickable*[]){&showRamButton});
List<UIElement*> elements(0, nullptr);
Window myWindow = Window(windowButtons, elements);

class SerialCommunicationThread : public Thread
{
  public:
    void Initialize()
    {
      Serial.begin(9600);
    }
    void Run()
    {
      Serial.print("\nOS Cycle Frequency: ");
      Serial.print(infoThread.GetCycleFrequency());
      Serial.println("Hz" );
      Serial.print("OS Cycle Time: ");
      Serial.print(infoThread.GetCycleTime());
      Serial.println("us" );
      Sleep(3000UL);
    }
};

SerialCommunicationThread serialThread = SerialCommunicationThread();


MicrOS os = MicrOS(nullptr);
ButtonDriver buttonDriver = ButtonDriver(os.GetInputManagerPtr(), /*button pins*/(uint8_t[]){6, 7, 11, 12}, /* number of button pins */ 4);
void setup()
{
  os.Start();
  os.AddThread(&buttonDriver);
  os.AddThread(&serialThread);
  os.AddThread(&infoThread);
  os.GetWindowManagerPtr()->SetActiveWindow(&myWindow);

}

void loop()
{
  os.Run();
}
