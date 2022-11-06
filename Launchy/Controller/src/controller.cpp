#include "controller.hpp"
#include "model.hpp"

std::string controller() {
	return std::string{ "Hi " } + std::to_string(model());
}