#include "Launcher.h"

Launcher::Launcher()
{
}

Launcher::~Launcher()
{
}

void Launcher::Update()
{
    _state = LauncherState::POP_UP;
}

void Launcher::PointerMoved(int x, int y)
{
}

void Launcher::PointerClicked(int x, int y)
{
}

void Launcher::Moved(Direction direction)
{
}
