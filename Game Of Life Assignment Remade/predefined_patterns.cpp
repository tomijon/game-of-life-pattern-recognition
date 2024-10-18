#include "predefined_patterns.hpp"


Target Base::blockPattern() {
	Pattern block;
	block.addCell(0, 0);
	block.addCell(0, 1);
	block.addCell(1, 0);
	block.addCell(1, 1);

	block.setPeriod(1);
	block.setOffset(0, 0);


	Target combine;
	combine.targets = new Pattern[1];
	combine.amount = 1;
	combine.targets[0] = block;
	combine.patternID = Base::BasePattern::BLOCK;
	return combine;
}

Target Base::beehivePattern() {
	Pattern vertical;
	vertical.addCell(1, 0);
	vertical.addCell(0, 1);
	vertical.addCell(0, 2);
	vertical.addCell(1, 3);
	vertical.addCell(2, 1);
	vertical.addCell(2, 2);
	vertical.setOffset(0, 0);
	vertical.setPeriod(1);

	Pattern horrizontal;
	horrizontal.addCell(0, 1);
	horrizontal.addCell(1, 0);
	horrizontal.addCell(2, 0);
	horrizontal.addCell(3, 1);
	horrizontal.addCell(1, 2);
	horrizontal.addCell(2, 2);
	horrizontal.setOffset(0, 0);
	horrizontal.setPeriod(1);

	Target combine;
	combine.targets = new Pattern[2];
	combine.amount = 2;
	combine.targets[0] = vertical;
	combine.targets[1] = horrizontal;
	combine.patternID = Base::BasePattern::BEEHIVE;
	return combine;
}


Target Base::blinkerPattern() {
	Pattern vertical;
	vertical.addCell(0, 0);
	vertical.addCell(0, 1);
	vertical.addCell(0, 2);
	vertical.setPeriod(2);
	vertical.setOffset(0, 0);

	Pattern horrizontal;
	horrizontal.addCell(0, 0);
	horrizontal.addCell(1, 0);
	horrizontal.addCell(2, 0);
	horrizontal.setPeriod(2);
	horrizontal.setOffset(0, 0);

	Target combine;
	combine.targets = new Pattern[2];
	combine.amount = 2;
	combine.targets[0] = vertical;
	combine.targets[1] = horrizontal;
	combine.patternID = Base::BasePattern::BLINKER;
	return combine;
}

Target Base::toadPattern() {
	Pattern vertical1;
	vertical1.addCell(0, 0);
	vertical1.addCell(0, 1);
	vertical1.addCell(0, 2);
	vertical1.addCell(1, 1);
	vertical1.addCell(1, 2);
	vertical1.addCell(1, 3);
	vertical1.setOffset(0, 0);
	vertical1.setPeriod(2);

	Pattern vertical2;
	vertical2.addCell(1, 0);
	vertical2.addCell(0, 1);
	vertical2.addCell(0, 2);
	vertical2.addCell(1, 1);
	vertical2.addCell(1, 2);
	vertical2.addCell(0, 3);

	Pattern vertical3;
	vertical3.addCell(1, 0);
	vertical3.addCell(0, 1);
	vertical3.addCell(0, 2);
	vertical3.addCell(2, 3);
	vertical3.addCell(3, 1);
	vertical3.addCell(3, 2);


	Pattern vertical4;
	vertical4.addCell(2, 0);
	vertical4.addCell(0, 1);
	vertical4.addCell(0, 2);
	vertical4.addCell(1, 3);
	vertical4.addCell(3, 1);
	vertical4.addCell(3, 2);


	Pattern horrizontal1;
	horrizontal1.addCell(1, 0);
	horrizontal1.addCell(2, 0);
	horrizontal1.addCell(3, 0);
	horrizontal1.addCell(0, 1);
	horrizontal1.addCell(1, 1);
	horrizontal1.addCell(2, 1);

	
	Pattern horrizontal2;
	horrizontal2.addCell(1, 0);
	horrizontal2.addCell(2, 0);
	horrizontal2.addCell(3, 1);
	horrizontal2.addCell(0, 0);
	horrizontal2.addCell(1, 1);
	horrizontal2.addCell(2, 1);


	Pattern horrizontal3;
	horrizontal3.addCell(1, 0);
	horrizontal3.addCell(2, 0);
	horrizontal3.addCell(3, 1);
	horrizontal3.addCell(2, 3);
	horrizontal3.addCell(1, 3);
	horrizontal3.addCell(0, 2);


	Pattern horrizontal4;
	horrizontal4.addCell(1, 0);
	horrizontal4.addCell(2, 0);
	horrizontal4.addCell(3, 2);
	horrizontal4.addCell(2, 3);
	horrizontal4.addCell(1, 3);
	horrizontal4.addCell(0, 1);

	Target combine;
	combine.targets = new Pattern[8];
	combine.amount = 8;
	combine.patternID = Base::BasePattern::TOAD;

	combine.targets[0] = vertical1;
	combine.targets[1] = vertical2;
	combine.targets[2] = vertical3;
	combine.targets[3] = vertical4;
	combine.targets[4] = horrizontal1;
	combine.targets[5] = horrizontal2;
	combine.targets[6] = horrizontal3;
	combine.targets[7] = horrizontal4;

	return combine;
}

Target Base::gliderPattern() {
	Target combine;
	return combine;
}

Target Base::lwssPattern() {
	Target combine;
	return combine;
}


Target Base::getPatterns(Base::BasePattern pattern) {
	switch (pattern) {
	case BLOCK:
		return blockPattern();
	case BEEHIVE:
		return beehivePattern();
	case BLINKER:
		return blinkerPattern();
	case TOAD:
		return toadPattern();
	case GLIDER:
		return gliderPattern();
	case LWSS:
		return lwssPattern();
	}
	return blockPattern();
}
