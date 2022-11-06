#include "model.hpp"


int model() {
	static int a;
	return ++a;
}