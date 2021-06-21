#include "SimpleTextBox.h"

#define BORDER_DISTANCE 4

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
    displayPtr->drawRBox(position.x - BORDER_DISTANCE, position.y - BORDER_DISTANCE, size.x + 8, size.y + 8, /* corner radius: */ 1);
  }
  else
  {
    //draw a rectangle
    displayPtr->drawRFrame(position.x - BORDER_DISTANCE, position.y - BORDER_DISTANCE, size.x + 8, size.y + 8, /* corner radius: */ 1);
  }
}

Vector2D SimpleTextBox::CalculateBoxSize(char * _text, U8G2 * displayPtr)
{
  //get the height and width of the text using the current font
  int textHeight = displayPtr->getMaxCharHeight() + 4;
  int textWidth = displayPtr->getStrWidth(_text) + 4;

  return Vector2D(textWidth, textHeight);
}
