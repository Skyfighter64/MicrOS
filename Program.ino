
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
  Main window design elements
*/

TextButton backButton = TextButton( Vector2D(0,50), "<", /*ID*/ 3, &BackClick);
TextButton upButton = TextButton( Vector2D(32,50), "^", /*ID*/ 2, &UpClick);
TextButton downButton = TextButton( Vector2D(64,50), "v", /*ID*/ 6, &DownClick);
TextButton okButton = TextButton( Vector2D(96,50), ">", /*ID*/ 5, &RightClick);
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
TextButton upButton2 = TextButton( Vector2D(32,50), "up", /*pin*/ 2, NULL);
TextButton downButton2 = TextButton( Vector2D(64,50), "down", /*pin*/ 6, NULL);
TextButton okButton2 = TextButton( Vector2D(96,50), "OK", /*pin*/ 5, NULL);
//TODO: adjust to new InputManager
List<Clickable*> secondUIButtons = List<Clickable*>(4, (Clickable*[]) {&backButton2, &upButton2, &downButton2, &okButton2});

TextBox ramBox = TextBox(/* position */ Vector2D(100, 10), /* text */ "");
UIText cycleTimeText = UIText( Vector2D(60, 30), "");
TextBox windowName = TextBox(Vector2D( 20, 10),"2nd Window");

List<UIElement*> secondWindowElements = List<UIElement*>(8, (UIElement*[]){&windowName,&ramBox, &cycleTimeText, &counter, &backButton2, &upButton2, &downButton2, &okButton2});

unsigned long timeMS = 0;

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
  Serial.print(F("Free memory:"));
  Serial.println(freeMemory());
  #endif


  //start the os
  os.Start();
  //add the button driver thread
  os.AddThread(&buttonDriver);
  os.GetWindowManager()->SetActiveWindow(&mainWindow);

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
    sprintf(mem_text_buff, "%dB", freeMemory());
    ramBox.uiText.text = mem_text_buff;

    //measure the cycle frequency in kHz and display it
    char time_text_buff[15];
    dtostrf((float) 1000000.0/(micros() - timeMS), 4, 2, time_text_buff);
    strcat(time_text_buff, "Hz");
    cycleTimeText.text = time_text_buff;
    timeMS = micros();

    #ifdef DEBUG
    Serial.print(F("Main Loop. i:"));
    Serial.println(i);
    Serial.print(F("Free memory:"));
    Serial.println(freeMemory());
    delay(500);
    #endif

  } while ( u8g2.nextPage() );

}


/*
  This section contains the code for calculating the remaining memory
*/
#ifdef __arm__
// should use uinstd.h to define sbrk but Due causes a conflict
extern "C" char* sbrk(int incr);
#else  // __ARM__
extern char *__brkval;
#endif  // __arm__

int freeMemory() {
  char top;
#ifdef __arm__
  return &top - reinterpret_cast<char*>(sbrk(0));
#elif defined(CORE_TEENSY) || (ARDUINO > 103 && ARDUINO != 151)
  return &top - __brkval;
#else  // __arm__
  return __brkval ? &top - __brkval : &top - __malloc_heap_start;
#endif  // __arm__
}
