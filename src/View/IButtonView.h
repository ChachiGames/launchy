#pragma once
#include "ButtonStyle.h"

class IView;

class IButtonView
{
public:
    virtual void Render(IView* view) = 0;

    virtual void Idle() = 0;
    virtual void Hover() = 0;
    virtual void OnClick() = 0;
    virtual bool IsOver(int x, int y) = 0;

protected:
    int _x, _y;           // position of the button
    int _width, _height;   // size of the button
    ButtonStyle _style;   // button style information (image, colors, etc.)  
};