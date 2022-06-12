#pragma once
#include "ButtonFactory.h"
#include "ButtonLogic.h"
#include "../View/IButtonView.h"
#include "../View/ButtonStyle.h"

#include <functional>
#include <utility>


class ButtonFactory
{
public:
    template<typename buttonType>
    static std::pair<ButtonLogic*, IButtonView*> CreateButton(int x, int y, int width, int height, ButtonStyle style, const std::function<void()> &clickCallback)
    {
        IButtonView* button = new buttonType(x, y, width, height, style);
        ButtonLogic* logic = new ButtonLogic(button, clickCallback);

        return {logic, button};    
    };
};