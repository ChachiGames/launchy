#pragma once

class IModel;
class SDLView;
class IButtonView;

class NavigationBar
{
public:
    NavigationBar(IModel* model, SDLView* view);
    ~NavigationBar();

    void Render();
    bool HitAnyButton(int x, int y);
private:
    const int _barHeight = 20;
    const int _buttonSize = 16;
    const int _buttonMargin = 10;

    IButtonView* _minimizeButton = nullptr;
    IButtonView* _closeButton = nullptr;

    SDLView* _view = nullptr;
};