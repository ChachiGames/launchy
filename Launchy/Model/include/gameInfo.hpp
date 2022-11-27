#pragma once

#include <string>
#include <filesystem>
#include <optional>


struct GameInfo {
	std::string name;
	std::string link;
	std::string description;
	std::string version;
	std::optional<std::filesystem::path> location;
};
