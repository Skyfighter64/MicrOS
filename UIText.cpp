#include "UIText.h"

UIText::UIText() : UIElement(), text(""), font(NULL)
{

}
UIText::UIText(char * _text): UIElement(), text(_text), font(NULL)
{

}
UIText::UIText(const uint8_t * _font, char * _text): UIElement(), text(_text), font(_font)
{

}
UIText::UIText(Vector2D _position, char * _text): UIElement(_position, Vector2D(0,0)), text(_text), font(NULL)
{

}
UIText::UIText(Vector2D _position, const uint8_t * _font, char * _text): UIElement(_position, Vector2D(0,0)), text(_text), font(_font)
{

}

void UIText::Draw(U8G2* display)
{
  //change the font
  const uint8_t * oldFont = SetFont(font, display);
  //draw the text to the display
  display->drawStr(position.x ,position.y ,text);
  //reset the font
  display->setFont(oldFont);
}

/*
  function setting the font
  @return: the font before applying the given font
    This can be used to reset the font
*/
uint8_t * UIText::SetFont(const uint8_t * font, U8G2 * display)
{
  //save the old font
  const uint8_t * oldFont = display->getU8g2()->font;

  //switch the font if a special font was given
  if(font != NULL)
  {
    display->setFont(font);
  }
  //set the font background to transparent
  display->setFontMode(1);
  //set the draw color to the inverted background color
  display->setDrawColor(2);

  return oldFont;
}
