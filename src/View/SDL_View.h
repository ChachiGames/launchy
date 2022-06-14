#pragma once
#include "IView.h"

#include <vector>

class IButtonView;
struct SDL_Renderer;
struct SDL_Window;
class Texture;

class SDLView: public IView
{
public:

	~SDLView();
	virtual int Init();

	virtual void ShowSplashArt();
	virtual void AddButton(IButtonView* button);

	// TODO: Change for a better data structure
	virtual void ShowGameInfo(int index);
	// TODO: Add other methods to show the info

	virtual void Render();


	SDL_Renderer* GetRenderer() { return _renderer; };
	SDL_Window* GetWindow() { return _window; };

	virtual int GetWidth();
	virtual int GetHeight();

private:

	virtual void Quit();

	std::vector<IButtonView*> _buttons;
	std::vector<Texture*> _textures;

	SDL_Window* _window = nullptr;
	SDL_Renderer* _renderer = nullptr;
};