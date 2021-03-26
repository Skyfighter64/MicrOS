#include "UIElement.h"


/*
 constructor
*/
UIElement::UIElement(): position(Vector2D()), size(Vector2D()), visible(true)
{

}

UIElement::UIElement(Vector2D _position, Vector2D _size): position(_position), size(_size), visible(true)
{

}
