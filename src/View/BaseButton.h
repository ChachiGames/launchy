#pragma once
#include "IButtonView.h"

class BaseButton: public IButtonView
{
public:

    virtual void Render(IView* view) = 0;

    virtual void Idle() = 0;
    virtual void Hover() = 0;
    virtual void OnClick() = 0;
    virtual bool IsOver(int x, int y);
};