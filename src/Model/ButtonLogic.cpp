#include "ButtonLogic.h"
#include "../View/IButtonView.h"

void ButtonLogic::Idle()
{
    _state = ButtonState::BTN_IDLE;
    _buttonView->Idle();
}

void ButtonLogic::OnHover()
{
    _state = ButtonState::BTN_HOVER;
    _buttonView->Hover();
}

void ButtonLogic::OnClicked()
{
    _state = ButtonState::BTN_CLICKED;
    _callback();
}

IButtonView* ButtonLogic::GetView() {return _buttonView;};

ButtonState ButtonLogic::GetState() {return _state;};