#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <Arduino.h>
#include "UIElement.h"
#include "UIText.h"




class TextBox : public UIElement
{
  public:
    UIText uiText;
    //flag indicating if this textbox is highlighted
    bool highlighted;
    //flag indicating if the textbox should rescale horizontally depending on the text
    bool autoscale;

    TextBox();
    TextBox(Vector2D _position, char * _text);
    TextBox(Vector2D _position,  const uint8_t * _font, char * _text);
    TextBox(Vector2D _position, Vector2D _size, char * _text);
    TextBox(Vector2D _position, Vector2D _size,const uint8_t * _font, char * _text);

    void Draw(U8G2 * displayPtr);

  protected:
    uint8_t * SetFont(const uint8_t * font, U8G2 * displayPtr);

  private:
    void DrawShape(U8G2 * displayPtr);
    void DrawContent(U8G2 * displayPtr);

    Vector2D CalculateTextPosition(U8G2 * displayPtr);
    Vector2D CalculateBoxSize(U8G2 * displayPtr);


};
#endif
