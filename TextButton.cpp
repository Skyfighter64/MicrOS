#include "TextButton.h"


/*
  Constructor for an automatically sized button depending on text
*/
TextButton::TextButton(U8G2 * _displayPtr, Vector2D _position, char * _text, uint8_t _inputID, void (* _OnClick)()): Clickable(_inputID, _OnClick), TextBox(TextBox(_displayPtr, _position, _text))
{

}

/*
  Constructor for an automatically sized button depending on text with font selection
*/
TextButton::TextButton(U8G2 * _displayPtr, Vector2D _position, char * _text, uint8_t _inputID, const uint8_t * _font, void (* _OnClick)()): Clickable(_inputID, _OnClick), TextBox(TextBox(_displayPtr, _position, _font, _text))
{

}


/*
  function overwriting TextBox::Draw
*/
void TextButton::Draw(U8G2 * displayPtr)
{
  //set TextBox::highlighted when the button is pressed
  //using the Clickable::state value
  highlighted = state;
  //draw the text box
  TextBox::Draw(displayPtr);
}
