
#include <Arduino.h> // for serial
#include <U8g2lib.h> //display API
#include <Bounce2.h> //for debouncing buttons

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
#include "TextButton.h"
#include "MicrOS.h"
#include "PushButton.h"
#include "Window.h"
#include "WindowManager.h"
#include "Clickable.h"
#include "List.h"
#include "ButtonDriver.h"
#include "SystemInfoThread.h"

#include "SleepTestThread.h"

//#define DEBUG




/*
TODO: delete pointers
https://stackoverflow.com/questions/3919850/conversion-from-myitem-to-non-scalar-type-myitem-requested

This does not need to be done until the broken MicrOS constructor gets fixed

TestThread.h can be removed

Create setText function for UIButton, UIText
*/



U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

/*
  declaration of the physical buttons
*/

//manager threads for the OS
WindowManager windowManager = WindowManager(&u8g2);
//TODO: adjust to new InputManager
InputManager inputManager = InputManager(&windowManager);

//os declaration
MicrOS os(&windowManager, &inputManager);



/*
  drivers for input
*/

ButtonDriver buttonDriver = ButtonDriver(&inputManager, /*button pins*/(uint8_t[]){2, 3, 5, 6}, 4);

/*
  custom threads
*/
SleepTestThread sleepTestThread = SleepTestThread();
SystemInfoThread systemInfoThread = SystemInfoThread();

/*
  Main window design elements
*/

TextButton backButton = TextButton( Vector2D(0,50), "<", /*input ID*/ 3, &BackClick);
TextButton upButton = TextButton( Vector2D(32,50), "^", /*input ID*/ 2, &UpClick);
TextButton downButton = TextButton( Vector2D(64,50), "v", /*input ID*/ 6, &DownClick);
TextButton okButton = TextButton( Vector2D(96,50), ">", /*input ID*/ 5, &RightClick);
List<Clickable*> windowButtons = List<Clickable*>(4, (Clickable*[]){&backButton, &upButton, &downButton, &okButton});

/*
    main window
*/




TextBox menuItem0 =  TextBox(/* position */ Vector2D(0, 16), /* font */ u8g2_font_open_iconic_app_2x_t, /* text */ "\x40");
TextBox menuItem1 =  TextBox(/* position */ Vector2D(40, 16), /* font */ u8g2_font_open_iconic_app_2x_t, /* text */ "\x41");
TextBox menuItem2 =  TextBox(/* position */ Vector2D(80, 16), /* font */ u8g2_font_open_iconic_app_2x_t, /* text */ "\x42");
//TextBox menuItem4 =  TextBox(/* position */ Vector2D(0, 32), /* font */ u8g2_font_open_iconic_app_2x_t, /* text */ "\x43");
//TextBox menuItem5 =  TextBox(/* position */ Vector2D(40, 32), /* font */ u8g2_font_open_iconic_app_2x_t, /* text */ "\x44");
//TextBox menuItem6 =  TextBox(/* position */ Vector2D(80, 32), /* font */ u8g2_font_open_iconic_app_2x_t, /* text */ "\x45");



UIText counter = UIText(/* position */ Vector2D(10, 10), /* text */ "");
List<UIElement*> windowElements = List<UIElement*>(8, (UIElement*[]) { &counter, &menuItem0, &menuItem1, &menuItem2, &backButton, &upButton, &downButton, &okButton});
Window mainWindow = Window(windowButtons, windowElements);

/*
    second window
*/

void BackClick2()
{
  //return to main window
  os.GetWindowManager()->SetActiveWindow(&mainWindow);
}

TextButton backButton2 = TextButton( Vector2D(0,50), "back", /*pin*/ 3, &BackClick2);
TextButton upButton2 = TextButton( Vector2D(32,50), "up", /*pin*/ 2, nullptr);
TextButton downButton2 = TextButton( Vector2D(64,50), "down", /*pin*/ 6, &DownClick);
TextButton okButton2 = TextButton( Vector2D(96,50), "OK", /*pin*/ 5, nullptr);
//TODO: adjust to new InputManager
List<Clickable*> secondUIButtons = List<Clickable*>(4, (Clickable*[]) {&backButton2, &upButton2, &downButton2, &okButton2});

TextBox ramBox = TextBox(/* position */ Vector2D(100, 10), /* text */ "");
UIText cycleTimeText = UIText(Vector2D(0, 36), "");
UIText cycleFrequencyText = UIText( Vector2D(60, 30), "");
TextBox windowName = TextBox(Vector2D( 20, 10),"2nd Window");
UIText sleepTestText = UIText(Vector2D(0,42), "");
UIText sleepDerivationText = UIText(Vector2D(0,48), "");


List<UIElement*> secondWindowElements = List<UIElement*>(11, (UIElement*[]){&sleepDerivationText, &sleepTestText, &windowName,&ramBox, &cycleTimeText, &cycleFrequencyText, &counter, &backButton2, &upButton2, &downButton2, &okButton2});

Window secondWindow = Window(secondUIButtons, secondWindowElements);


/*
  OnClick functions for the main window
*/

int i = 0;

void IncreaseCounter()
{
  i++;

}

void DecreaseCounter()
{
  i--;
}

void BackClick()
{
  DecreaseCounter();
}

void UpClick()
{
  IncreaseCounter();
}

void DownClick()
{
  buttonDriver.Sleep(1000);
}

void RightClick()
{
 //i = 100;
 os.GetWindowManager()->SetActiveWindow(&secondWindow);

}

/*
  list of all windows
*/
// This may not be needed TODO: decide
//List<Window*> windows = List<Window*>(1, (Window*[]) {&mainWindow});



void setup() {

  //set up the display
  u8g2.begin();
  u8g2.setFont(u8g2_font_tinytim_tf);

  #ifdef DEBUG
  Serial.begin(9600);

  Serial.println(F("Size of:"));
  Serial.print(F("InputManager: "));
  Serial.println(sizeof(InputManager));
  Serial.print(F("WindowManager: "));
  Serial.println(sizeof(WindowManager));
  Serial.print(F("Thread: "));
  Serial.println(sizeof(Thread));
  Serial.print(F("MicrOS: "));
  Serial.println(sizeof(MicrOS));
  Serial.print(F("PushButton: "));
  Serial.println(sizeof(PushButton));
  Serial.print(F("TextButton: "));
  Serial.println(sizeof(TextButton));
  Serial.print(F("TextBox: "));
  Serial.println(sizeof(TextBox));
  Serial.print(F("UIButton: "));
  Serial.println(sizeof(UIButton));
  Serial.print(F("UIText: "));
  Serial.println(sizeof(UIText));
  Serial.print(F("UIElement: "));
  Serial.println(sizeof(UIElement));
  Serial.print(F("Vector2D: "));
  Serial.println(sizeof(Vector2D));
  Serial.print(F("Window: "));
  Serial.println(sizeof(Window));
  Serial.print(F("Clickable: "));
  Serial.println(sizeof(Clickable));
  Serial.print(F("ButtonDriver: "));
  Serial.println(sizeof(ButtonDriver));
  Serial.print(F("SystemInfoThread: "));
  Serial.println(sizeof(SystemInfoThread));
  Serial.print(F("SleepTestThread: "));
  Serial.println(sizeof(SleepTestThread));
  Serial.print(F("List<Thread*>: "));
  Serial.println(sizeof(List<Thread*>));
  #endif


  //start the os
  os.Start();
  //add the button driver thread
  os.AddThread(&buttonDriver);
  os.GetWindowManager()->SetActiveWindow(&secondWindow);

  //add custom threads
  os.AddThread(&systemInfoThread);
  os.AddThread(&sleepTestThread);
}


void loop() {
  // put your main code here, to run repeatedly:

 u8g2.firstPage();
  do {
    //run one OS cycle
    os.Run();

    /*
      TODO: check if this can be done cleaner, eg. inside a special thread
    */

    //update the UI
    char i_buff[4];
    sprintf(i_buff, "%d", i);
    counter.text = i_buff;

    char mem_text_buff[5];
    sprintf(mem_text_buff, "%dB", systemInfoThread.GetFreeMemory());
    ramBox.uiText.text = mem_text_buff;

    //measure the cycle frequency in Hz and display it
    char frequency_text_buff[15];
    dtostrf(systemInfoThread.GetCycleFrequency(), 4, 2, frequency_text_buff);
    strcat(frequency_text_buff, "Hz");
    cycleFrequencyText.text = frequency_text_buff;

    char time_text_buff[23];
    sprintf(time_text_buff, "CycleTime: %dms", systemInfoThread.GetCycleTime()/1000);
    cycleTimeText.text = time_text_buff;


    /*
      test sleeping accuracy
    */
    //print out sleep delta
    char sleep_buff[20];
    sprintf(sleep_buff, "delta: %ums", sleepTestThread.GetDelta());
    sleepTestText.text = sleep_buff;

    //print out sleep delta percentage
//    char der_buff[15];
//    sprintf(der_buff,"perc: %d%%", sleepTestThread.GetDeltaPercentage());
//    sleepDerivationText.text = der_buff;




    #ifdef DEBUG
    Serial.print(F("Main Loop. i:"));
    Serial.println(i);
    Serial.print(F("Free memory:"));
    Serial.println(systemInfoThread.GetFreeMemory());
    //delay(500);
    #endif

  } while ( u8g2.nextPage() );

}
