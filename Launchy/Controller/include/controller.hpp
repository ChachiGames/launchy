#pragma once

#include <string>
#include <vector>
#include <memory>
#include "model.hpp"

std::string controller();


class Controller {
public:
	Controller(const View& view);
	
	//Client -> Model
	[[nodiscard]] std::vector<GameInfo> getGames() const;
	void launchGame   (const GameInfo& gameInfo) const;
	void updateGame   (const GameInfo& gameInfo) const;
	void installGame  (const GameInfo& gameInfo) const;
	void uninstallGame(const GameInfo& gameInfo) const;

	//Model -> Client
	void showMessage(const Message&);
private:
	std::unique_ptr<Model> _model;
	const View& _view;
};
