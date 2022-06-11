#include "IModel.h"

class Launcher : public IModel
{
public:
	Launcher();
	~Launcher();

	// Logic goes here
	void Update();

	// Mouse and other analogic controllers
	void PointerMoved(int x, int y);
	void PointerClicked(int x, int y);

	// Gamepads and other digital controllers
	void Moved(Direction direction);
};