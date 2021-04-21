#include "SimpleTextBox.h"

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
  UIText::size = CalculateTextSize(text, displayPtr);
  UIText::text = text;
}

void SimpleTextBox::Draw(U8G2 * displayPtr)
{
  //draw the box
  DrawShape(displayPtr);
  //draw the text
  UIText::Draw(displayPtr);
}

void SimpleTextBox::DrawShape(U8G2 * displayPtr)
{
  //set the draw color to the inverted background color
  displayPtr->setDrawColor(1);

  //check if the box is highlighted
  if(highlighted)
  {
    //draw a box
    displayPtr->drawRBox(position.x - 4, position.y - 4, size.x + 8, size.y + 8, /* corner radius: */ 1);
  }
  else
  {
    //draw a rectangle
    displayPtr->drawRFrame(position.x - 4, position.y - 4, size.x + 8, size.y + 8, /* corner radius: */ 1);
  }
}

Vector2D SimpleTextBox::CalculateTextSize(char * text, U8G2 * displayPtr)
{
  //get the height and width of the text using the current font
  Vector2D textSize = Vector2D();
  textSize.x = displayPtr->getStrWidth(text);
  textSize.y = displayPtr->getMaxCharHeight();
}
