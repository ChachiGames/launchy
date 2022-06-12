#pragma once
#include "IButtonView.h"

#include <cstdint>

struct ButtonStyle;

class ButtonViewTest: public IButtonView
{
public:
    ButtonViewTest(int x, int y, int width, int height, ButtonStyle style);

    virtual void Render(IView* view);

    virtual void Idle();
    virtual void Hover();
    virtual void OnClick();
    virtual bool IsOver(int x, int y);

private:
    uint32_t _currentColor;
};