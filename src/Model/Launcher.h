#pragma once
#include "IModel.h"
#include "View/IView.h"
#include "Controller/IController.h"


class Launcher : public IModel
{
public:
	Launcher();
	virtual ~Launcher();

	virtual int Init(IView* view, IController* controller) override;

	// Logic goes here
	virtual void Update() override;

	// Mouse and other analogic controllers
	virtual void PointerMoved(int x, int y) override;
	virtual void PointerClicked(int x, int y) override;

	// Gamepads and other digital controllers
	virtual void Moved(Direction direction) override;
private:
	IView* _view;
	IController* _controller;
};