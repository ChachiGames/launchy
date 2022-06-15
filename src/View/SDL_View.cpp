#include "SDL_View.h"
#include "IButtonView.h"
#include "Texture.h"
#include "NavigationBar.h"
#include "Model/IModel.h"

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

SDLView::~SDLView()
{
    delete _navigationBar;
    Quit();
}

SDL_HitTestResult MyCallback(SDL_Window* win, const SDL_Point* area, void* data)
{

    // Early check to not process if any navigation button is pressed
    if(((NavigationBar*)data)->HitAnyButton(area->x, area->y))
        return SDL_HITTEST_NORMAL;

    // Left some margins for scaling the window
    int margins = 5;
    int menuBarHeight = 20; // hard-coded until there is a proper menu bar. This is just a concept
    
    int w,h;
    SDL_GetWindowSize(win, &w, &h);
    
    //Checks if inside the rectangle
    if(area->x >= margins && area->x < w - margins && area->y >= margins && area->y < menuBarHeight)
    {
        return SDL_HITTEST_DRAGGABLE;
    }
    
    // Checks how it should be scaled depending on the y axis
    if(area->x >= 0 && area->x < margins)
    {
       if(area->y >= 0 && area->y < margins) return SDL_HITTEST_RESIZE_TOPLEFT;
       if(area->y >= margins && area->y < h - margins) return SDL_HITTEST_RESIZE_LEFT;
       return SDL_HITTEST_RESIZE_BOTTOMLEFT;
    }

    else if(area->x >= margins && area->x < w - margins)
    {
        if(area->y >= 0 && area->y < margins) return SDL_HITTEST_RESIZE_TOP;
        if(area->y >= h - margins && area->y < h) return SDL_HITTEST_RESIZE_BOTTOM;
    }

    else if(area->x >= w - margins && area->x < w)
    {
       if(area->y >= 0 && area->y < margins) return SDL_HITTEST_RESIZE_TOPRIGHT;
       if(area->y >= margins && area->y < h - margins) return SDL_HITTEST_RESIZE_RIGHT;
       return SDL_HITTEST_RESIZE_BOTTOMRIGHT;
    }

    return SDL_HITTEST_NORMAL;
}


int SDLView::Init(IModel* model)
{

    // Initialisation
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Unable to init SDL : %s", SDL_GetError());
        return 1;
    }

    if(!( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ))
    {
        printf("Unable to init SDL_Image : %s", IMG_GetError());
        return 1;
    }
    
    _window = SDL_CreateWindow("Launchy", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN|SDL_WINDOW_BORDERLESS);
    if (_window == NULL) {
        printf("Unable to create window : %s", SDL_GetError());
        return 1;
    }
    
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (_renderer == NULL) {
        printf("Unable to create renderer : %s", SDL_GetError());
        return 1;
    }

    _navigationBar = new NavigationBar(model, this);


    SDL_SetWindowResizable(_window, SDL_TRUE);
    SDL_SetWindowHitTest(_window, MyCallback, _navigationBar);

    return 0;
}

void SDLView::ShowSplashArt()
{
    Texture* t = new Texture(this);
    if(!t->LoadFromFile("./logo.png"))
        std::cout << "Failed loading logo.png" << std::endl;
    else
        _textures.push_back(t);
}

void SDLView::AddButton(IButtonView* button)
{
    _buttons.push_back(button);
}

int SDLView::GetWidth()
{
    int w,h;
    SDL_GetWindowSize(_window,&w,&h);
    return w;
}

int SDLView::GetHeight()
{
    int w,h;
    SDL_GetWindowSize(_window,&w,&h);
    return h;
}

void SDLView::Quit()
{
    for(auto* b : _buttons)
        delete b;
    for(auto* t : _textures)
        delete t;
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);
    SDL_Quit();
}

void SDLView::ShowGameInfo(int index)
{

}

void SDLView::Render()
{
    SDL_SetRenderDrawColor(_renderer, 0,0,0,255);

    // Clear screen
    SDL_RenderClear(_renderer);

    // render code goes here.....
    for(int i = 0; i < _buttons.size(); i++)
    {
        _buttons[i]->Render(this);
    }
    for(Texture* t : _textures)
    {
        t->Render(0,0);
    }

    _navigationBar->Render();
    // Render modification
    SDL_RenderPresent(_renderer);
}
