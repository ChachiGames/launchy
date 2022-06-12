#pragma once
#include "IView.h"

class SDLView: public IView
{
public:

	virtual int Init();
	virtual void Quit();

	// TODO: Change for a better data structure
	virtual void ShowGameInfo(int index);
	// TODO: Add other methods to show the info

	virtual void Render();

private:
	struct SDL_Window* _window = nullptr;
	struct SDL_Renderer* _renderer = nullptr;
};