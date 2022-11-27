#include "controller.hpp"
#include "model.hpp"


Controller::Controller(const View& view)
	: _view(view), _model(std::make_unique<Model>(*this)){};


[[nodiscard]] std::vector<GameInfo> Controller::getGames() const { return _model.get()->getGames(); };
void Controller::launchGame(const GameInfo& gameInfo) const { _model.get()->launchGame(gameInfo); };
void Controller::updateGame(const GameInfo& gameInfo) const { _model.get()->updateGame(gameInfo); };
void Controller::installGame(const GameInfo& gameInfo) const { _model.get()->installGame(gameInfo); };
void Controller::uninstallGame(const GameInfo& gameInfo) const { _model.get()->uninstallGame(gameInfo); };