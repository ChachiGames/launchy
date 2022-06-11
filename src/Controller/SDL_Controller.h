#pragma once
#include "IController.h"

class SDLController: public IController
{
public:
	SDLController();
	virtual ~SDLController();

	virtual void Init(IModel* model, void* windowHandle);
	virtual void Update();
};
