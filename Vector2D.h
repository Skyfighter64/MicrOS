#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <Arduino.h>
/*
 Class for representing a vector in 2D space
*/
/*
  TODO: add comparison operations
*/

class Vector2D
{
  public:
    uint8_t x;
    uint8_t y;
    Vector2D();
    Vector2D(uint8_t _x, uint8_t _y);
};

#endif
