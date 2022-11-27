#include <filesystem>
#include <fstream>
#include <iostream>

#include "model.hpp"
#include "modelConfiguration.hpp"

#include "cpr/cpr.h"
#include "fmt/format.h"
#include "nlohmann/json.hpp"

Model::Model(Controller& controller) :_controller(controller) {
	using json = nlohmann::json; 
	namespace fs = std::filesystem;
	const std::string URLToLauncherInfo = "https://drive.google.com/uc?export=download&id=1R2IDUuxK_IgGtqCyp8FmErElbButmIgc";
	auto response = cpr::Get(cpr::Url(URLToLauncherInfo));

	json gamesJson;
	if (response.status_code == 0) {
		fmt::print("Error {} - {}", (int)response.error.code, response.error.message);
	}
	else if(response.status_code >= 400 && response.status_code < 500) {
		fmt::print("Error '{}-{}' while trying to access {}", response.status_code, response.text, URLToLauncherInfo);
	}
	else {
		gamesJson = json::parse(response.text);
		for (auto game : gamesJson)
		{
			_gameIndexes.insert({ game["Name"], (int)_games.size()});
			_games.emplace_back(GameInfo{ game["Name"], game["Link"],"",game["Version"],std::nullopt});
		}
	}


	fs::path localPathToGames = "./games.json";
	if(fs::exists(localPathToGames))
	{
		json localGames = json::parse(std::ifstream(localPathToGames));
		std::cout << localGames;
	}
	else {
		std::ofstream gameFile(localPathToGames);
		gameFile << gamesJson.dump();
	}
}

[[nodiscard]] std::vector<GameInfo> Model::getGames() const {
	return _games;
}

void Model::launchGame(const GameInfo& gameInfo) const {
	(void)gameInfo; 
}

void Model::updateGame(const GameInfo& gameInfo) const {
	(void)gameInfo; 
}

void Model::installGame(const GameInfo& gameInfo) const { 
	(void)gameInfo; 
}

void Model::uninstallGame(const GameInfo& gameInfo) const { 
	(void)gameInfo; 
}