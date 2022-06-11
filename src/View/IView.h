#pragma once

class IView
{
public:

	virtual void Init() = 0;

	// TODO: Change for a better data structure
	virtual void ShowGameInfo(int index) = 0;
	// TODO: Add other methods to show the info

	virtual void Update() = 0;
};