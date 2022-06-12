#pragma once
#include "IController.h"

class SDLController: public IController
{
public:
	SDLController();
	virtual ~SDLController();

	virtual int Init(IModel* model, void* windowHandle);
	virtual bool Update();
private:
	IModel* _model;
};
