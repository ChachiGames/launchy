#include "controller.hpp"

#include <iostream>

#include "fmt/format.h"

int main(int argc, char* argv[]) {
	(void)argc;
	(void)argv;
	std::cout << "HOLI FROM VIEW" << std::endl;

	fmt::print("HOLA [{0}]\n", controller());

	return 0;
}