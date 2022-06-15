#include "ButtonViewTest.h"
#include "SDL_View.h"

#include <SDL.h>
#include <iostream>

ButtonViewTest::ButtonViewTest(int x, int y, int width, int height, ButtonStyle style)
{
    _x = x;
    _y = y;
    _width = width;
    _height = height;
    _style = style;

    Idle();
}

void ButtonViewTest::Render(IView* view)
{
    SDL_Renderer* renderer = (*(SDLView*)view).GetRenderer();
    SDL_Rect rectangle{};
    int x = _x, y = _y;
    if(_style.relativeX)
    {
        int w = (*(SDLView*)view).GetWidth();
        _windowW = w;
        x=w+_x;
    }
    if(_style.relativeY)
    {
        int h = (*(SDLView*)view).GetHeight();
        _windowH = h;
        y = h+_y;
    }
    rectangle = {x, y, _width, _height};
    
    SDL_SetRenderDrawColor(renderer, _currentColor >> 24, (_currentColor & 0x00FF0000) >> 16, (_currentColor & 0x0000FF00) >> 8, (_currentColor & 0x000000FF));
    SDL_RenderFillRect(renderer, &rectangle);
}

bool ButtonViewTest::IsOver(int x, int y)
{
    int ourX = _x, ourY = _y;
    if(_style.relativeX)
    {
        int w = _windowW;
        ourX = w+_x;
    }
    if(_style.relativeY)
    {
        int h = _windowH;
        ourY = h+_y;
    }

    return  x >= ourX && x < ourX + _width &&
            y >= ourY && y < ourY + _height;
}

void ButtonViewTest::Idle()
{
    _currentColor = _style.color;
}

void ButtonViewTest::Hover()
{
    _currentColor = _style.hoverColor;
}

void ButtonViewTest::OnClick()
{
    _currentColor = _style.clickedColor;
}
