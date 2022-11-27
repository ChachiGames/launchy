#pragma once
#include "gameInfo.hpp"


#include <vector>
#include <unordered_map>

class View {};
struct Message {};

struct ModelConfiguration;

class Controller;

class Model {
public:
	Model(Controller&);

	[[nodiscard]] std::vector<GameInfo> getGames() const;
	void launchGame   (const GameInfo& gameInfo) const;
	void updateGame   (const GameInfo& gameInfo) const;
	void installGame  (const GameInfo& gameInfo) const;
	void uninstallGame(const GameInfo& gameInfo) const;

private:
	Controller& _controller;
	std::vector<GameInfo> _games;
	std::unordered_map<std::string, int> _gameIndexes;
};