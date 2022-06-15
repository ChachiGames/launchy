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
    rectangle = {_x, _y, _width, _height};
    
    SDL_SetRenderDrawColor(renderer, _currentColor >> 24, (_currentColor & 0x00FF0000) >> 16, (_currentColor & 0x0000FF00) >> 8, (_currentColor & 0x000000FF));
    SDL_RenderFillRect(renderer, &rectangle);
}

bool ButtonViewTest::IsOver(int x, int y)
{
    return  x >= _x && x < _x + _width &&
            y >= _y && y < _y + _height;
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
