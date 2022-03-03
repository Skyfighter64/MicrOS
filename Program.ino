
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
#include "TextBox.h"
#include "MicrOS.h"
#include "PushButton.h"
#include "Window.h"
#include "WindowManager.h"
#include "Clickable.h"
#include "List.h"

//input drivers
#include "ButtonDriver.h"
#include "IRNecDriver.h"

//custom threads
#include "SystemInfoThread.h"
#include "SleepTestThread.h"

#define DEBUG

U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);


//os declaration
MicrOS os(&u8g2);



/*
  input drivers
*/

ButtonDriver buttonDriver = ButtonDriver(os.GetInputManagerPtr(), /*button pins*/(uint8_t[]){6, 7, 11, 12}, /* number of button pins */ 4);
IRNecDriver irDriver = IRNecDriver(os.GetInputManagerPtr());

/*
  custom threads
*/
SleepTestThread sleepTestThread = SleepTestThread();
SystemInfoThread systemInfoThread = SystemInfoThread();

/*
  Main window design elements
*/
TextButton backButton = TextButton(&u8g2, Vector2D(0,50), "<", /*input ID*/ 12, &BackClick);
TextButton upButton = TextButton(&u8g2, Vector2D(32,50), "^", /*input ID*/ 11, &UpClick);
TextButton downButton = TextButton(&u8g2, Vector2D(64,50), "v", /*input ID*/ 6, &DownClick);
TextButton okButton = TextButton(&u8g2, Vector2D(96,50), ">", /*input ID*/ 7, &RightClick);
List<Clickable*> windowButtons = List<Clickable*>(4, (Clickable*[]){&backButton, &upButton, &downButton, &okButton});

/*
    main window
*/
//TextBox menuItem0 =  TextBox(/* position */ Vector2D(0, 16), /* font */ u8g2_font_open_iconic_app_2x_t, /* text */ "\x40");
//TextBox menuItem1 =  TextBox(/* position */ Vector2D(40, 16), /* font */ u8g2_font_open_iconic_app_2x_t, /* text */ "\x41");
//TextBox menuItem2 =  TextBox(/* position */ Vector2D(80, 16), /* font */ u8g2_font_open_iconic_app_2x_t, /* text */ "\x42");
//TextBox menuItem4 =  TextBox(/* position */ Vector2D(0, 32), /* font */ u8g2_font_open_iconic_app_2x_t, /* text */ "\x43");
//TextBox menuItem5 =  TextBox(/* position */ Vector2D(40, 32), /* font */ u8g2_font_open_iconic_app_2x_t, /* text */ "\x44");
//TextBox menuItem6 =  TextBox(/* position */ Vector2D(80, 32), /* font */ u8g2_font_open_iconic_app_2x_t, /* text */ "\x45");



UIText counter = UIText(/* position */ Vector2D(10, 10), /* text */ "");
List<UIElement*> windowElements = List<UIElement*>(5, (UIElement*[]) { &counter, /*&menuItem0, &menuItem1, &menuItem2,*/ &backButton, &upButton, &downButton, &okButton});
Window mainWindow = Window(windowButtons, windowElements);

/*
    second window
*/

void BackClick2()
{
  //return to main window
  os.GetWindowManagerPtr()->SetActiveWindow(&mainWindow);
}

TextButton backButton2 = TextButton(&u8g2, Vector2D(0,55), "back", /*pin*/ 12, &BackClick2);
TextButton upButton2 = TextButton(&u8g2, Vector2D(32,55), "Up", /*pin*/ 11, nullptr);
TextButton downButton2 = TextButton(&u8g2, Vector2D(64,55), "Down", /*pin*/ 6, /*u8g2_font_mademoiselle_mel_tr,*/ &FreezeInputs);
TextButton okButton2 = TextButton(&u8g2, Vector2D(96,55), "OK", /*pin*/ 7, &ChangeButtonText);
List<Clickable*> secondClickables = List<Clickable*>(4, (Clickable*[]) {&backButton2, &upButton2, &downButton2, &okButton2});

TextBox ramBox = TextBox(/* position */ Vector2D(100, 10), /* text */ "");
UIText cycleTimeText = UIText(Vector2D(0, 36), "");
UIText cycleFrequencyText = UIText( Vector2D(60, 30), "");
SimpleTextBox windowName = SimpleTextBox(&u8g2, Vector2D( 20, 10),"2nd Window");
UIText sleepTestText = UIText(Vector2D(0,42), "");
UIText sleepDerivationText = UIText(Vector2D(0,48), "");


List<UIElement*> secondWindowElements = List<UIElement*>(11, (UIElement*[]){&sleepDerivationText, &sleepTestText, &windowName,&ramBox, &cycleTimeText, &cycleFrequencyText, &counter, &backButton2, &upButton2, &downButton2, &okButton2});

Window secondWindow = Window(secondClickables, secondWindowElements);


/*
  OnClick functions for the main window
*/

int i = 0;

void ChangeButtonText()
{
  okButton2.SetText("Ok2", &u8g2);
}
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
  os.GetWindowManagerPtr()->Sleep(2000);
}

void UpClick()
{
  IncreaseCounter();
}

void DownClick()
{
  DecreaseCounter();
}
void FreezeInputs()
{
  buttonDriver.Sleep(2000);
}

void RightClick()
{
 //i = 100;
 os.GetWindowManagerPtr()->SetActiveWindow(&secondWindow);

}



void setup() {

  //set up the display
  u8g2.begin();
  u8g2.setFont(u8g2_font_tinytim_tf);
  windowName.SetText("2nd Window", &u8g2);
  #ifdef DEBUG
  Serial.begin(9600);

  // print out the size of each object in bytes for optimizing memory usage
  Serial.println(F("\nSize of:"));
  Serial.print(F("InputManager: "));
  Serial.println(sizeof(InputManager));
  Serial.print(F("WindowManager: "));
  Serial.println(sizeof(WindowManager));
  Serial.print(F("SystemInfoThread: "));
  Serial.println(sizeof(SystemInfoThread));
  Serial.print(F("SleepTestThread: "));
  Serial.println(sizeof(SleepTestThread));
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
  Serial.print(F("IRNecDriver: "));
  Serial.println(sizeof(IRNecDriver));
  Serial.print(F("List<Thread*>: "));
  Serial.println(sizeof(List<Thread*>));
  Serial.print(F("SimpleTextBox: "));
  Serial.println(sizeof(SimpleTextBox));
  #endif


  //start the os
  os.Start();
  //add the button driver thread
  os.AddThread(&buttonDriver);
  os.AddThread(&irDriver);
  os.GetWindowManagerPtr()->SetActiveWindow(&secondWindow);

  //add custom threads
  os.AddThread(&systemInfoThread);
  os.AddThread(&sleepTestThread);

}

uint8_t result = 0;

void loop() {
  // put your main code here, to run repeatedly:


    os.Run();


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
    sprintf(time_text_buff, "CycleTime: %dus", systemInfoThread.GetCycleTime());
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




}
