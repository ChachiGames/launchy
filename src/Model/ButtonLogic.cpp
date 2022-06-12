#include "ButtonLogic.h"
#include "../View/IButtonView.h"

void ButtonLogic::OnHover()
{
    _buttonView->Hover();
}

void ButtonLogic::OnClicked()
{
    _callback();
}