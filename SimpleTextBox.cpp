#include "SimpleTextBox.h"

//offset of the box to the text position
#define Y_OFFSET 8
#define X_OFFSET 2

SimpleTextBox::SimpleTextBox(U8G2 * _displayPtr, Vector2D _position, char * _text) : UIText(_position, nullptr)
{
  SetText(_text, _displayPtr);
}
SimpleTextBox::SimpleTextBox(U8G2 * _displayPtr, Vector2D _position,  const uint8_t * _font, char * _text): UIText(_position, _font, nullptr)
{
  SetText(_text, _displayPtr);
}


void SimpleTextBox::SetText(char* text, U8G2 * displayPtr)
{
  UIText::size = CalculateBoxSize(text, displayPtr);
  UIText::text = text;
}

void SimpleTextBox::Draw(U8G2 * displayPtr)
{
  //set the font if needed
  const uint8_t * oldFont = SetFont(UIText::font, displayPtr);
  //draw the text
  UIText::Draw(displayPtr);
  //draw the box
  DrawShape(displayPtr);

  //reset the font
  displayPtr->setFont(oldFont);
}

void SimpleTextBox::DrawShape(U8G2 * displayPtr)
{
  //set the draw color to the inverted background color
  displayPtr->setDrawColor(1);

  //check if the box is highlighted
  if(highlighted)
  {
    //draw a box
    displayPtr->drawRBox(position.x - X_OFFSET, position.y - Y_OFFSET, size.x, size.y, /* corner radius: */ 1);
  }
  else
  {
    //draw a rectangle
    displayPtr->drawRFrame(position.x - X_OFFSET, position.y - Y_OFFSET, size.x, size.y, /* corner radius: */ 1);
  }
}

Vector2D SimpleTextBox::CalculateBoxSize(char * _text, U8G2 * displayPtr)
{
  //get the height and width of the text using the current font
  int textHeight = displayPtr->getMaxCharHeight() + (Y_OFFSET / 2);
  int textWidth = displayPtr->getStrWidth(_text) + X_OFFSET * 2;

  return Vector2D(textWidth, textHeight);
}
