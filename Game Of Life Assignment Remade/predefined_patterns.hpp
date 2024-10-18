#pragma once

#include "pattern.hpp"

using namespace Patterns;

namespace Base {

	enum BasePattern {
		NONE = 1 << 0,
		BLOCK = 1 << 1,
		BEEHIVE = 1 << 2,
		BLINKER = 1 << 3,
		TOAD = 1 << 4,
		GLIDER = 1 << 5,
		LWSS = 1 << 6
	};

	const string names[7] = {
		"none",
		"block", "beehive",
		"blinker", "toad",
		"glider", "lwss"
	};


	Target nonePattern();
	Target blockPattern();
	Target beehivePattern();
	Target blinkerPattern();
	Target toadPattern();
	Target gliderPattern();
	Target lwssPattern();

	Patterns::Target getPatterns(BasePattern pattern);
}
