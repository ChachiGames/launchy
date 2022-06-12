#pragma once

class IView
{
public:

	virtual int Init() = 0;
	virtual void Quit() = 0;

	// TODO: Change for a better data structure
	virtual void ShowGameInfo(int index) = 0;
	// TODO: Add other methods to show the info

	virtual void Render() = 0;

};