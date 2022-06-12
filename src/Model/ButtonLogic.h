#pragma once
#include <functional>
class IButtonView;

class ButtonLogic
{
public:
    ButtonLogic(IButtonView* view, std::function<void()> callback): _buttonView(view), _callback(callback) {};
    virtual void OnHover();
    virtual void OnClicked();
protected:
    IButtonView* _buttonView = nullptr;
    std::function<void()> _callback;
};