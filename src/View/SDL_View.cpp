#include "SDL_View.h"
#include <SDL.h>
#include <iostream>

SDLView::~SDLView()
{
    Quit();
}

int SDLView::Init()
{

    // Initialisation
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Unable to init SDL : %s", SDL_GetError());
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

    return 0;
}

void SDLView::Quit()
{
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);
    SDL_Quit();
}
void SDLView::ShowGameInfo(int index)
{

}

void SDLView::Render()
{
    
        // Clear screen
        SDL_RenderClear(_renderer);

        // render code goes here.....

        // Render modification
        SDL_RenderPresent(_renderer);
}
