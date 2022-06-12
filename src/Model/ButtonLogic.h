#pragma once
#include <functional>
class IButtonView;

enum class ButtonState {BTN_IDLE = 0, BTN_HOVER, BTN_CLICKED};

class ButtonLogic
{
public:
    ButtonLogic(IButtonView* view, std::function<void()> callback): _buttonView(view), _callback(callback) {};

    void Idle();
    void OnHover();
    void OnClicked();

    IButtonView* GetView();
    ButtonState GetState();
protected:
    IButtonView* _buttonView = nullptr;
    std::function<void()> _callback;
    ButtonState _state = ButtonState::BTN_IDLE;
};