#pragma once
#include "../Model/IModel.h"

class IController
{
public:

	virtual int Init(IModel* model, void* windowHandle) = 0;

	virtual bool Update() = 0;

protected:

	IModel* _model = nullptr;
	void* _windowHandle = nullptr;
};
