#include "SplashArt.h"
#include "Texture.h"
#include "SDL_View.h"

#include <iostream>

SplashArt::SplashArt(SDLView* view, float fadeTime, float offsetTime): Texture(view)
{
    _active = true;
    _fadingTime = fadeTime;
    _timeActive = fadeTime + offsetTime;
    SetBlendMode(SDL_BLENDMODE_BLEND);
}

void SplashArt::Animate(float deltaTime)
{
    // To avoid over-calculations
    if(!_active) return;

    _timeActive -= deltaTime;

    if(_timeActive - _fadingTime <= 0)
        SetAlpha((255 * _timeActive) / _fadingTime);

    if(_timeActive <= 0)
        _active = false;
}

bool SplashArt::IsActive()
{
    return _active;
}

void SplashArt::SetActive(bool active)
{
    _active = active;
}