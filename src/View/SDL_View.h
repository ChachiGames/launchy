#pragma once
#include "IView.h"

#include <vector>

class IButtonView;
struct SDL_Renderer;

class SDLView: public IView
{
public:

	~SDLView();
	virtual int Init();

	virtual void AddButton(IButtonView* button);

	// TODO: Change for a better data structure
	virtual void ShowGameInfo(int index);
	// TODO: Add other methods to show the info

	virtual void Render();


	SDL_Renderer* GetRenderer() { return _renderer; };

private:

	virtual void Quit();

	std::vector<IButtonView*> _buttons;

	struct SDL_Window* _window = nullptr;
	struct SDL_Renderer* _renderer = nullptr;
};