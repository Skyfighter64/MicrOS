#ifndef UITEXT_H
#define UITEXT_H

#include <Arduino.h>
#include "UIElement.h"
#include "Vector2D.h"
#include <U8g2lib.h>


class UIText : public UIElement
{
  public:
    char * text;
    uint8_t * font;

    UIText();
    UIText(char * _text);
    UIText(const uint8_t * _font, char * _text);
    UIText(Vector2D _position, char * _text);
    UIText(Vector2D _position, const uint8_t * _font, char * _text);
    void Draw(U8G2* display);

  protected:
    uint8_t * SetFont(const uint8_t * font, U8G2 * display);
};

#endif
