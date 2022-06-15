#pragma once

class IButtonView;
class IModel;

class IView
{
public:

	virtual int Init(IModel* model) = 0;
	virtual void Quit() = 0;

	virtual void ShowSplashArt() = 0;
	virtual void AddButton(IButtonView* button) = 0;
	// TODO: Change for a better data structure
	virtual void ShowGameInfo(int index) = 0;
	// TODO: Add other methods to show the info

	virtual void Render() = 0;
	virtual int GetWidth() = 0;
	virtual int GetHeight() = 0;
};