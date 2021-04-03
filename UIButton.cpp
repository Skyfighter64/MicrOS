#include "UIButton.h"

//default constructor
UIButton::UIButton(Vector2D _position, Vector2D _size, uint8_t _inputID, void (* _OnClick)()): UIElement(_position, _size), Clickable(_inputID, _OnClick)
{

}
