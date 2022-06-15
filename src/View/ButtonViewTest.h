#pragma once
#include "BaseButton.h"

#include <cstdint>

struct ButtonStyle;

class ButtonViewTest: public BaseButton
{
public:
    ButtonViewTest(int x, int y, int width, int height, ButtonStyle style);

    virtual void Render(IView* view);
    virtual bool IsOver(int x, int y) override;

    virtual void Idle();
    virtual void Hover();
    virtual void OnClick();

private:
    uint32_t _currentColor;
    int _windowW;
    int _windowH;
};