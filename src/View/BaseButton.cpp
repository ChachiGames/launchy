#include "BaseButton.h"

bool BaseButton::IsOver(int x, int y)
{
    return  x >= _x && x < _x + _width &&
            y >= _y && y < _y + _height;
}