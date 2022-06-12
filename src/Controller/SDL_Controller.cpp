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
    _model = model;
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
        if(event.type == SDL_MOUSEMOTION)
        {
            _model->PointerMoved(event.motion.x, event.motion.y);
        }
        if(event.type == SDL_MOUSEBUTTONDOWN)
        {
            _model->PointerClicked(event.button.x, event.button.y);
        }

    }
    return true;
}
