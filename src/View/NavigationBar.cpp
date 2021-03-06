#include "Model/IModel.h"
#include "Model/ButtonFactory.h"
#include "SDL_View.h"
#include "ButtonStyle.h"
#include "NavigationBar.h"
#include "ButtonViewTest.h"

#include <utility>
#include <functional>
#include <iostream>


#include <SDL.h>


NavigationBar::NavigationBar(IModel* model, SDLView* view)
{
    _view = view;
    SDL_Window* window = _view->GetWindow();
    int windowWidth = view->GetWidth();
    int upperMargin = (int)((_barHeight - _buttonSize) * 0.5f);
    
    ButtonStyle style = {0x00CA4EFF, "", 0x00CA4EFF, 0x00CA4EFF};
    std::pair<ButtonLogic*, IButtonView*> minButton = ButtonFactory::CreateButton<ButtonViewTest>(windowWidth - 2 * _buttonMargin - 2 * _buttonSize, upperMargin, _buttonSize, _buttonSize, style, 
    [window]() 
    {
        std::cout << "Minimize" <<std::endl;
        SDL_MinimizeWindow(window);
    });

    model->AddButton(minButton.first);
    _minimizeButton = minButton.second;

    style.color = 0xFF605CFF;
    style.hoverColor = 0xFF605CFF;
    style.clickedColor = 0xFF605CFF;
    
    std::pair<ButtonLogic*, IButtonView*> closeButton = ButtonFactory::CreateButton<ButtonViewTest>(windowWidth - _buttonMargin - _buttonSize, upperMargin, _buttonSize, _buttonSize, style, 
    [model]() 
    {
        std::cout << "quit" <<std::endl;
        model->Quit();
    });

    model->AddButton(closeButton.first);
    _closeButton = closeButton.second;

}
NavigationBar::~NavigationBar()
{
    delete _minimizeButton;
    delete _closeButton;
}

bool NavigationBar::HitAnyButton(int x, int y){
    return _minimizeButton->IsOver(x,y) || _closeButton->IsOver(x,y);
}

void NavigationBar::Render()
{
    SDL_Rect rectangle;
    rectangle.x = 0;
    rectangle.y = 0;
    SDL_GetWindowSize(_view->GetWindow(), &rectangle.w, nullptr);
    rectangle.h = _barHeight;
    SDL_SetRenderDrawColor(_view->GetRenderer(), 255,255,255,255);

    SDL_RenderFillRect(_view->GetRenderer(), &rectangle);

    _minimizeButton->Render(_view);
    _closeButton->Render(_view);
}