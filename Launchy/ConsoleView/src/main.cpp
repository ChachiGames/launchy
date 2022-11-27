#include "controller.hpp"

#include <iostream>

#include "fmt/format.h"
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include "ftxui/component/component.hpp" 

int main(int argc, char* argv[]) {
	using namespace  ftxui;
	(void)argc;
	(void)argv;
	View v;

	Controller c(v);

	auto games = c.getGames();
	for (auto game : games) {
		std::cout <<game.name << " " << game.version << "\n";
	}
	
	
	std::cout << "wat";
	return 0;
}
