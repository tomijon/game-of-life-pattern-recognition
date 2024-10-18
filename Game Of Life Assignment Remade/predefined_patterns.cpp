#include "predefined_patterns.hpp"


Target Base::nonePattern() {
	Pattern none;
	none.setPeriod(1);
	none.setOffset(0, 0);

	Target combine;
	combine.targets = new Pattern[1];
	combine.amount = 1;
	combine.targets[0] = none;
	combine.patternID = Base::BasePattern::NONE;
	return combine;
}


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
	combine.amount = 0;
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
	vertical2.setOffset(0, 0);
	vertical2.setPeriod(2);

	Pattern vertical3;
	vertical3.addCell(1, 0);
	vertical3.addCell(0, 1);
	vertical3.addCell(0, 2);
	vertical3.addCell(2, 3);
	vertical3.addCell(3, 1);
	vertical3.addCell(3, 2);
	vertical3.setOffset(0, 0);
	vertical3.setPeriod(2);


	Pattern vertical4;
	vertical4.addCell(2, 0);
	vertical4.addCell(0, 1);
	vertical4.addCell(0, 2);
	vertical4.addCell(1, 3);
	vertical4.addCell(3, 1);
	vertical4.addCell(3, 2);
	vertical4.setOffset(0, 0);
	vertical4.setPeriod(2);


	Pattern horrizontal1;
	horrizontal1.addCell(1, 0);
	horrizontal1.addCell(2, 0);
	horrizontal1.addCell(3, 0);
	horrizontal1.addCell(0, 1);
	horrizontal1.addCell(1, 1);
	horrizontal1.addCell(2, 1);
	horrizontal1.setOffset(0, 0);
	horrizontal1.setPeriod(2);

	
	Pattern horrizontal2;
	horrizontal2.addCell(1, 0);
	horrizontal2.addCell(2, 0);
	horrizontal2.addCell(3, 1);
	horrizontal2.addCell(0, 0);
	horrizontal2.addCell(1, 1);
	horrizontal2.addCell(2, 1);
	horrizontal2.setOffset(0, 0);
	horrizontal2.setPeriod(2);


	Pattern horrizontal3;
	horrizontal3.addCell(1, 0);
	horrizontal3.addCell(2, 0);
	horrizontal3.addCell(3, 1);
	horrizontal3.addCell(2, 3);
	horrizontal3.addCell(1, 3);
	horrizontal3.addCell(0, 2);
	horrizontal3.setOffset(0, 0);
	horrizontal3.setPeriod(2);


	Pattern horrizontal4;
	horrizontal4.addCell(1, 0);
	horrizontal4.addCell(2, 0);
	horrizontal4.addCell(3, 2);
	horrizontal4.addCell(2, 3);
	horrizontal4.addCell(1, 3);
	horrizontal4.addCell(0, 1);
	horrizontal4.setOffset(0, 0);
	horrizontal4.setPeriod(2);

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
	Pattern stage1TR;
	stage1TR.addCell(1, 2);
	stage1TR.addCell(2, 1);
	stage1TR.addCell(2, 0);
	stage1TR.addCell(1, 0);
	stage1TR.addCell(0, 0);
	stage1TR.setOffset(-1, 1);
	stage1TR.setPeriod(4);

	Pattern stage2TR;
	stage2TR.addCell(0, 2);
	stage2TR.addCell(2, 2);
	stage2TR.addCell(2, 1);
	stage2TR.addCell(1, 1);
	stage2TR.addCell(1, 0);
	stage2TR.setOffset(-1, 1);
	stage2TR.setPeriod(4);

	Pattern stage3TR;
	stage3TR.addCell(0, 1);
	stage3TR.addCell(1, 0);
	stage3TR.addCell(2, 0);
	stage3TR.addCell(2, 1);
	stage3TR.addCell(2, 2);
	stage3TR.setOffset(-1, 1);
	stage3TR.setPeriod(4);

	Pattern stage4TR;
	stage4TR.addCell(0, 2);
	stage4TR.addCell(0, 0);
	stage4TR.addCell(1, 0);
	stage4TR.addCell(1, 1);
	stage4TR.addCell(2, 1);
	stage4TR.setOffset(-1, 1);
	stage4TR.setPeriod(4);

	Pattern stage1TL;
	stage1TL.addCell(1, 2);
	stage1TL.addCell(0, 1);
	stage1TL.addCell(0, 0);
	stage1TL.addCell(1, 0);
	stage1TL.addCell(2, 0);
	stage1TL.setOffset(1, 1);
	stage1TL.setPeriod(4);

	Pattern stage2TL;
	stage2TL.addCell(2, 2);
	stage2TL.addCell(0, 2);
	stage2TL.addCell(0, 1);
	stage2TL.addCell(1, 1);
	stage2TL.addCell(1, 0);
	stage2TL.setOffset(1, 1);
	stage2TL.setPeriod(4);

	Pattern stage3TL;
	stage3TL.addCell(2, 1);
	stage3TL.addCell(1, 0);
	stage3TL.addCell(0, 0);
	stage3TL.addCell(0, 1);
	stage3TL.addCell(0, 2);
	stage3TL.setOffset(1, 1);
	stage3TL.setPeriod(4);

	Pattern stage4TL;
	stage4TL.addCell(2, 2);
	stage4TL.addCell(2, 0);
	stage4TL.addCell(1, 0);
	stage4TL.addCell(1, 1);
	stage4TL.addCell(0, 1);
	stage4TL.setOffset(1, 1);
	stage4TL.setPeriod(4);

	Pattern stage1BR;
	stage1BR.addCell(1, 0);
	stage1BR.addCell(2, 1);
	stage1BR.addCell(2, 2);
	stage1BR.addCell(1, 2);
	stage1BR.addCell(0, 2);
	stage1BR.setOffset(-1, -1);
	stage1BR.setPeriod(4);

	Pattern stage2BR;
	stage2BR.addCell(0, 0);
	stage2BR.addCell(2, 0);
	stage2BR.addCell(2, 1);
	stage2BR.addCell(1, 1);
	stage2BR.addCell(1, 2);
	stage2BR.setOffset(-1, -1);
	stage2BR.setPeriod(4);

	Pattern stage3BR;
	stage3BR.addCell(0, 1);
	stage3BR.addCell(1, 2);
	stage3BR.addCell(2, 2);
	stage3BR.addCell(2, 1);
	stage3BR.addCell(2, 0);
	stage3BR.setOffset(-1, -1);
	stage3BR.setPeriod(4);

	Pattern stage4BR;
	stage4BR.addCell(0, 0);
	stage4BR.addCell(0, 2);
	stage4BR.addCell(1, 2);
	stage4BR.addCell(1, 1);
	stage4BR.addCell(2, 1);
	stage4BR.setOffset(-1, -1);
	stage4BR.setPeriod(4);

	Pattern stage1BL;
	stage1BL.addCell(1, 0);
	stage1BL.addCell(0, 1);
	stage1BL.addCell(0, 2);
	stage1BL.addCell(1, 2);
	stage1BL.addCell(2, 2);
	stage1BL.setOffset(1, -1);
	stage1BL.setPeriod(4);

	Pattern stage2BL;
	stage2BL.addCell(2, 0);
	stage2BL.addCell(0, 0);
	stage2BL.addCell(0, 1);
	stage2BL.addCell(1, 1);
	stage2BL.addCell(1, 2);
	stage2BL.setOffset(1, -1);
	stage2BL.setPeriod(4);

	Pattern stage3BL;
	stage3BL.addCell(2, 1);
	stage3BL.addCell(1, 2);
	stage3BL.addCell(0, 2);
	stage3BL.addCell(0, 1);
	stage3BL.addCell(0, 0);
	stage3BL.setOffset(1, -1);
	stage3BL.setPeriod(4);

	Pattern stage4BL;
	stage4BL.addCell(2, 0);
	stage4BL.addCell(2, 2);
	stage4BL.addCell(1, 2);
	stage4BL.addCell(1, 1);
	stage4BL.addCell(0, 1);
	stage4BL.setOffset(1, -1);
	stage4BL.setPeriod(4);

	Target combine;
	combine.amount = 16;
	combine.targets = new Pattern[16];
	combine.targets[0] = stage1BL;
	combine.targets[1] = stage2BL;
	combine.targets[2] = stage3BL;
	combine.targets[3] = stage4BL;
	combine.targets[4] = stage1BR;
	combine.targets[5] = stage2BR;
	combine.targets[6] = stage3BR;
	combine.targets[7] = stage4BR;
	combine.targets[8] = stage1TL;
	combine.targets[9] = stage2TL;
	combine.targets[10] = stage3TL;
	combine.targets[11] = stage4TL;
	combine.targets[12] = stage1TR;
	combine.targets[13] = stage2TR;
	combine.targets[14] = stage3TR;
	combine.targets[15] = stage4TR;
	combine.patternID = Base::BasePattern::GLIDER;
	return combine;
}

Target Base::lwssPattern() {
	Pattern stage1R;
	stage1R.addCell(0, 1);
	stage1R.addCell(0, 3);
	stage1R.addCell(1, 0);
	stage1R.addCell(2, 0);
	stage1R.addCell(3, 0);
	stage1R.addCell(3, 3);
	stage1R.addCell(4, 0);
	stage1R.addCell(4, 1);
	stage1R.addCell(4, 2);
	stage1R.setOffset(-1, 0);
	stage1R.setPeriod(4);

	Pattern stage2R;
	stage2R.addCell(0, 1);
	stage2R.addCell(0, 2);
	stage2R.addCell(1, 0);
	stage2R.addCell(1, 1);
	stage2R.addCell(1, 2);
	stage2R.addCell(2, 0);
	stage2R.addCell(2, 1);
	stage2R.addCell(2, 3);
	stage2R.addCell(3, 1);
	stage2R.addCell(3, 2);
	stage2R.addCell(3, 3);
	stage2R.addCell(4, 2);
	stage2R.setOffset(-1, 0);
	stage2R.setPeriod(4);

	Pattern stage3R;
	stage3R.addCell(0, 2);
	stage3R.addCell(0, 0);
	stage3R.addCell(1, 3);
	stage3R.addCell(2, 3);
	stage3R.addCell(3, 3);
	stage3R.addCell(3, 0);
	stage3R.addCell(4, 3);
	stage3R.addCell(4, 2);
	stage3R.addCell(4, 1);
	stage3R.setOffset(-1, 0);
	stage3R.setPeriod(4);

	Pattern stage4R;
	stage4R.addCell(0, 2);
	stage4R.addCell(0, 1);
	stage4R.addCell(1, 3);
	stage4R.addCell(1, 2);
	stage4R.addCell(1, 1);
	stage4R.addCell(2, 3);
	stage4R.addCell(2, 2);
	stage4R.addCell(2, 0);
	stage4R.addCell(3, 2);
	stage4R.addCell(3, 1);
	stage4R.addCell(3, 0);
	stage4R.addCell(4, 1);
	stage4R.setOffset(-1, 0);
	stage4R.setPeriod(4);


	Pattern stage1L;
	stage1L.addCell(4, 1);
	stage1L.addCell(4, 3);
	stage1L.addCell(3, 0);
	stage1L.addCell(2, 0);
	stage1L.addCell(1, 0);
	stage1L.addCell(1, 3);
	stage1L.addCell(0, 0);
	stage1L.addCell(0, 1);
	stage1L.addCell(0, 2);
	stage1L.setOffset(1, 0);
	stage1L.setPeriod(4);

	Pattern stage2L;
	stage2L.addCell(4, 1);
	stage2L.addCell(4, 2);
	stage2L.addCell(3, 0);
	stage2L.addCell(3, 1);
	stage2L.addCell(3, 2);
	stage2L.addCell(2, 0);
	stage2L.addCell(2, 1);
	stage2L.addCell(2, 3);
	stage2L.addCell(1, 1);
	stage2L.addCell(1, 2);
	stage2L.addCell(1, 3);
	stage2L.addCell(0, 2);
	stage2L.setOffset(1, 0);
	stage2L.setPeriod(4);

	Pattern stage3L;
	stage3L.addCell(4, 2);
	stage3L.addCell(4, 0);
	stage3L.addCell(3, 3);
	stage3L.addCell(2, 3);
	stage3L.addCell(1, 3);
	stage3L.addCell(1, 0);
	stage3L.addCell(0, 3);
	stage3L.addCell(0, 2);
	stage3L.addCell(0, 1);
	stage3L.setOffset(1, 0);
	stage3L.setPeriod(4);

	Pattern stage4L;
	stage4L.addCell(4, 2);
	stage4L.addCell(4, 1);
	stage4L.addCell(3, 3);
	stage4L.addCell(3, 2);
	stage4L.addCell(3, 1);
	stage4L.addCell(2, 3);
	stage4L.addCell(2, 2);
	stage4L.addCell(2, 0);
	stage4L.addCell(1, 2);
	stage4L.addCell(1, 1);
	stage4L.addCell(1, 0);
	stage4L.addCell(0, 1);
	stage4L.setOffset(1, 0);
	stage4L.setPeriod(4);

	Pattern stage1U;
	stage1U.addCell(0, 0);
	stage1U.addCell(0, 1);
	stage1U.addCell(0, 2);
	stage1U.addCell(0, 3);
	stage1U.addCell(1, 0);
	stage1U.addCell(1, 4);
	stage1U.addCell(2, 0);
	stage1U.addCell(3, 1);
	stage1U.addCell(3, 4);
	stage1U.setOffset(0, 1);
	stage1U.setPeriod(4);

	Pattern stage2U;
	stage2U.addCell(0, 2);
	stage2U.addCell(0, 3);
	stage2U.addCell(1, 1);
	stage2U.addCell(1, 2);
	stage2U.addCell(1, 3);
	stage2U.addCell(1, 4);
	stage2U.addCell(2, 0);
	stage2U.addCell(2, 1);
	stage2U.addCell(2, 3);
	stage2U.addCell(2, 4);
	stage2U.addCell(3, 1);
	stage2U.addCell(3, 2);
	stage2U.setOffset(0, 1);
	stage2U.setPeriod(4);

	Pattern stage3U;
	stage3U.addCell(3, 0);
	stage3U.addCell(3, 1);
	stage3U.addCell(3, 2);
	stage3U.addCell(3, 3);
	stage3U.addCell(2, 0);
	stage3U.addCell(2, 4);
	stage3U.addCell(1, 0);
	stage3U.addCell(0, 1);
	stage3U.addCell(0, 4);
	stage3U.setOffset(0, 1);
	stage3U.setPeriod(4);

	Pattern stage4U;
	stage4U.addCell(3, 2);
	stage4U.addCell(3, 3);
	stage4U.addCell(2, 1);
	stage4U.addCell(2, 2);
	stage4U.addCell(2, 3);
	stage4U.addCell(2, 4);
	stage4U.addCell(1, 0);
	stage4U.addCell(1, 1);
	stage4U.addCell(1, 3);
	stage4U.addCell(1, 4);
	stage4U.addCell(0, 1);
	stage4U.addCell(0, 2);
	stage4U.setOffset(0, 1);
	stage4U.setPeriod(4);

	Pattern stage1D;
	stage1D.addCell(0, 4);
	stage1D.addCell(0, 3);
	stage1D.addCell(0, 2);
	stage1D.addCell(0, 1);
	stage1D.addCell(1, 4);
	stage1D.addCell(1, 0);
	stage1D.addCell(2, 4);
	stage1D.addCell(3, 3);
	stage1D.addCell(3, 0);
	stage1D.setOffset(0, -1);
	stage1D.setPeriod(4);

	Pattern stage2D;
	stage2D.addCell(0, 2);
	stage2D.addCell(0, 1);
	stage2D.addCell(1, 3);
	stage2D.addCell(1, 2);
	stage2D.addCell(1, 1);
	stage2D.addCell(1, 0);
	stage2D.addCell(2, 4);
	stage2D.addCell(2, 3);
	stage2D.addCell(2, 1);
	stage2D.addCell(2, 0);
	stage2D.addCell(3, 3);
	stage2D.addCell(3, 2);
	stage2D.setOffset(0, -1);
	stage2D.setPeriod(4);

	Pattern stage3D;
	stage3D.addCell(3, 4);
	stage3D.addCell(3, 3);
	stage3D.addCell(3, 2);
	stage3D.addCell(3, 1);
	stage3D.addCell(2, 4);
	stage3D.addCell(2, 0);
	stage3D.addCell(1, 4);
	stage3D.addCell(0, 3);
	stage3D.addCell(0, 0);
	stage3D.setOffset(0, -1);
	stage3D.setPeriod(4);

	Pattern stage4D;
	stage4D.addCell(3, 2);
	stage4D.addCell(3, 1);
	stage4D.addCell(2, 3);
	stage4D.addCell(2, 2);
	stage4D.addCell(2, 1);
	stage4D.addCell(2, 0);
	stage4D.addCell(1, 4);
	stage4D.addCell(1, 3);
	stage4D.addCell(1, 1);
	stage4D.addCell(1, 0);
	stage4D.addCell(0, 3);
	stage4D.addCell(0, 2);
	stage4D.setOffset(0, -1);
	stage4D.setPeriod(4);


	Target combine;
	combine.amount = 16;
	combine.targets = new Pattern[16];
	combine.patternID = Base::BasePattern::LWSS;

	combine.targets[0] = stage1R;
	combine.targets[1] = stage2R;
	combine.targets[2] = stage3R;
	combine.targets[3] = stage4R;
	combine.targets[4] = stage1L;
	combine.targets[5] = stage2L;
	combine.targets[6] = stage3L;
	combine.targets[7] = stage4L;
	combine.targets[8] = stage1U;
	combine.targets[9] = stage2U;
	combine.targets[10] = stage3U;
	combine.targets[11] = stage4U;
	combine.targets[12] = stage1D;
	combine.targets[13] = stage2D;
	combine.targets[14] = stage3D;
	combine.targets[15] = stage4D;

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
