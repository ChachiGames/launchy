#include "SDL_Controller.h"
#include "SDL.h"

SDLController::SDLController()
{
}

SDLController::~SDLController()
{
}

int SDLController::Init(IModel* model, void* windowHandle)
{
    return 0;
}

bool SDLController::Update()
{
    SDL_Event event;

    if (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return false;
        }
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
            return false;
        }

    }
    return true;
}
