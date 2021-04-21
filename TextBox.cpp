#include "TextBox.h"

/*
  default constructo
*/
TextBox::TextBox() : UIElement(), uiText(UIText()), highlighted(false), autoscale(true)
{

}

/*
 autoscaling constructor
*/
TextBox::TextBox(Vector2D _position, char * _text): UIElement(_position, Vector2D()), uiText(UIText(_text)), highlighted(false), autoscale(true)
{

}
/*
 autoscaling constructor with font selection
*/
TextBox::TextBox(Vector2D _position, const uint8_t * _font, char * _text): UIElement(_position, Vector2D()), uiText(UIText( _font, _text)), highlighted(false), autoscale(true)
{

}
/*
manual scaling constructor
*/
TextBox::TextBox(Vector2D _position, Vector2D _size, char * _text): UIElement(_position, _size), uiText(UIText(_text)), highlighted(false), autoscale(false)
{

}
/*
manual scaling constructor with font selection
*/
TextBox::TextBox(Vector2D _position, Vector2D _size, const uint8_t * _font, char * _text): UIElement(_position, _size), uiText(UIText(_font, _text)), highlighted(false), autoscale(false)
{

}



void TextBox::Draw(U8G2 * displayPtr)
{
  //set the font if needed
  const uint8_t * oldFont = SetFont(uiText.font, displayPtr);

  if(autoscale)
  {
    size = CalculateBoxSize(displayPtr);
  }

  DrawShape(displayPtr);
  DrawContent(displayPtr);

  //reset the font
  displayPtr->setFont(oldFont);
}



/*
  function drawing the box surrounding the text
*/
void TextBox::DrawShape(U8G2 * displayPtr)
{
  //set the draw color to the inverted background color
  displayPtr->setDrawColor(1);

  if(highlighted)
  {
    //draw a box
    displayPtr->drawRBox(position.x, position.y, size.x, size.y , /* corner radius: */ 1);
  }
  else
  {
    //draw a rectangle
    displayPtr->drawRFrame(position.x, position.y, size.x, size.y , /* corner radius: */ 1);
  }
}



/*
  Function drawing the content of the button to the screen
*/
void TextBox::DrawContent(U8G2 * displayPtr)
{
  //cacluclate the position of the text so it is centered
  uiText.position = CalculateTextPosition(displayPtr);
  uiText.Draw(displayPtr);
}




/*
  Function calculating the postiton of the text within the button so it is centered
*/
Vector2D TextBox::CalculateTextPosition(U8G2 * displayPtr)
{
  //get the height and width of the text using the current font
  int textHeight = displayPtr->getMaxCharHeight();
  int textWidth = displayPtr->getStrWidth(uiText.text);

  Vector2D result = Vector2D();
  result.x = position.x + ((size.x - textWidth) / 2);
  result.y = position.y + ((size.y + textHeight) / 2);

  return result;
}



/*
  Function calculating a size for the button so the text fits
*/
Vector2D TextBox::CalculateBoxSize(U8G2 * displayPtr)
{
  //get the height and width of the text using the current font
  int textHeight = displayPtr->getMaxCharHeight() + 4;
  int textWidth = displayPtr->getStrWidth(uiText.text) + 4;

  return Vector2D(textWidth, textHeight);
}


/*
  function setting the font
  @return: the font before applying the given font
    This can be used to reset the font
*/
uint8_t * TextBox::SetFont(const uint8_t * font, U8G2 * displayPtr)
{
  //get the current font
  uint8_t * oldFont = displayPtr->getU8g2()->font;
  //set the font if possible
  if(font != nullptr)
  {
    displayPtr->setFont(font);
  }
  //return the old font
  return oldFont;
}
