#pragma once
#include "Texture.h"

class SDLView;
class SplashArt: public Texture
{
public:
    SplashArt(SDLView* view, float fadeTime, float offsetTime);

    void Animate(float deltaTime);

    bool IsActive();
    void SetActive(bool active);

private:
    float _fadingTime;  // Time used for the fade out effect
    float _timeActive;  
    bool _active;
};