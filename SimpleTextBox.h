#ifndef SIMPLE_TEXT_BOX_H
#define SIMPLE_TEXT_BOX_H

#include <U8g2lib.h>
#include "UIText.h"
#include "Clickable.h"
#include "Vector2D.h"

/*
  A simple text box with minimal features for maximum efficiency
*/
class SimpleTextBox : public UIText
{
public:
  //default constructor
  SimpleTextBox(U8G2 * _displayPtr, Vector2D _position, char * _text);
  //constructor with font selection
  SimpleTextBox(U8G2 * _displayPtr, Vector2D _position,  const uint8_t * _font, char * _text);
  //setter for the text
  void SetText(char* text, U8G2 * displayPtr);
  //override UIText::Draw()
  void Draw(U8G2 * displayPtr);

  bool highlighted;

protected:
  //function calculating the size of the text in pixel
  Vector2D CalculateBoxSize(char* _text, U8G2 * display);
private:
  //function drawing the box
  void DrawShape(U8G2 * displayPtr);
};
#endif