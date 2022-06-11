#pragma once
#include "../Model/IModel.h"

class IController
{
public:

	virtual void Init(IModel* model, void* windowHandle) = 0;

	virtual void Update() = 0;

protected:

	IModel* _model = nullptr;
	void* _windowHandle = nullptr;
};
