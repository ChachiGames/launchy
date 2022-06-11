#pragma once
#include "IView.h"

class SDLView: public IView
{
public:

	virtual void Init();

	// TODO: Change for a better data structure
	virtual void ShowGameInfo(int index);
	// TODO: Add other methods to show the info

	virtual void Update();
};