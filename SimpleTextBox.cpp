#include "SimpleTextBox.h"
#include <U8g2lib.h>

// Padding size of the box borders in pixel
#define PADDING 2

SimpleTextBox::SimpleTextBox(U8G2 * _displayPtr, Vector2D _position, char * _text) : UIText(_position, nullptr)
{
  SetText(_text, _displayPtr);
}
SimpleTextBox::SimpleTextBox(U8G2 * _displayPtr, Vector2D _position,  const uint8_t * _font, char * _text): UIText(_position, _font, nullptr)
{

  UIText::font = _font;
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
  //TODO: this may not be needed as UIText::Draw already sets the font
  const uint8_t * oldFont = SetFont(UIText::font, displayPtr);
  //draw the box
  DrawShape(displayPtr);
  //draw the text
  UIText::Draw(displayPtr);

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
    displayPtr->drawRBox(position.x - PADDING, position.y - size.y + PADDING, size.x, size.y, /* corner radius: */ 1);
  }
  else
  {
    //set the draw color to cover any background color
    displayPtr->setDrawColor(1);
    //draw a rectangle
    displayPtr->drawRFrame(position.x - PADDING, position.y - size.y + PADDING, size.x, size.y, /* corner radius: */ 1);
  }
}


Vector2D SimpleTextBox::CalculateBoxSize(char * _text, U8G2 * _displayPtr)
{
  //apply the text font for size calculations
  uint8_t* oldFont = SetFont(UIText::font, _displayPtr);

  // initialize the font if not set yet
  // this occours when initializing this object before u8g2.begin() is called
  if (_displayPtr->getU8g2()->font == nullptr)
  {
    // set u8g2_font_tinytim_tf as default font if no font was set yet
    _displayPtr->setFont(u8g2_font_tinytim_tf);
  }

  //get the height and width of the text using the current font
  int textHeight = _displayPtr->getMaxCharHeight();
  int textWidth = _displayPtr->getStrWidth(_text);

  //reset the font
  SetFont(oldFont, _displayPtr);
  return Vector2D(textWidth + (PADDING*2), textHeight + PADDING);
}
