#pragma once
enum class LauncherState { HOME = 0, GAME_SELECTED, POP_UP };
enum class Direction { UP = 0, DOWN, LEFT, RIGHT };

class IModel
{
public:

	// Logic goes here
	virtual void Update() = 0;

	// Mouse and other analogic controllers
	virtual void PointerMoved(int x, int y) = 0;
	virtual void PointerClicked(int x, int y) = 0;

	// Gamepads and other digital controllers
	virtual void Moved(Direction direction) = 0;

protected:
	LauncherState _state = LauncherState::HOME;
};