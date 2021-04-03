
#include "TextButton.h"



/*
  default constructor
*/
TextButton::TextButton(Vector2D _position, Vector2D _size, char * _text, uint8_t _inputID, void (* _OnClick)()): UIButton(_position, _size, _inputID, _OnClick), textBox(TextBox(_position, _size, _text))
{

}

/*
  default constructor with font selection
*/
TextButton::TextButton(Vector2D _position, Vector2D _size, char * _text, uint8_t _inputID, const uint8_t * _font, void (* _OnClick)()): UIButton(_position, _size, _inputID, _OnClick), textBox(TextBox(_position, _size, _font, _text))
{

}

/*
  Constructor for an automatically sized button depending on text
*/
TextButton::TextButton( Vector2D _position, char * _text, uint8_t _inputID, void (* _OnClick)()): UIButton(_position, Vector2D(), _inputID, _OnClick), textBox(TextBox(_position, _text))
{

}

/*
  Constructor for an automatically sized button depending on text with font selection
*/
TextButton::TextButton( Vector2D _position, char * _text, uint8_t _inputID, const uint8_t * _font, void (* _OnClick)()): UIButton(_position, Vector2D(), _inputID, _OnClick), textBox(TextBox(_position, _font, _text))
{

}



/*
  function overwriting UIButton::Draw
*/
void TextButton::Draw(U8G2 * display)
{
  //highlight the textBox when the button is pressed
  //using the Clickable::state value
  textBox.highlighted = state;
  //draw the textBox
  textBox.Draw(display);
}
