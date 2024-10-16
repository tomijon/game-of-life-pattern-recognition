#include "cell.hpp"


void GameOfLife::World::update() {
	unordered_set<Point, PointHash> newAliveLocations;

	for (auto map : cells) {
		Cell* cell = map.second;

		if (not cell->isValid()) continue;

		int alive = 0;
		for (int n = 0; n < NEIGHBORS; n++) {
			if (cell->getNeighbor(n) == nullptr) continue;
			if (cell->getNeighbor(n)->isAlive()) alive++;
		}
		if (alive == 3) newAliveLocations.insert(cell->getPosition());
		else if (alive == 2 and cell->isAlive()) newAliveLocations.insert(cell->getPosition());
	}
	clearCells();

	for (Point p : newAliveLocations) {
		setAliveCell(p);
	}
	createNeighbors();
	assignRegions();
	vector<Patterns::Region> regions = makeRegions();
	addToHistory();
	checkHistory(regions);
	gen++;
}


vector<Patterns::Region> GameOfLife::World::makeRegions() {
	vector<Patterns::Region> regions;

	for (pair<Point, Cell*> map : cells) {
		Cell* cell = map.second;
		if (not cell->hasRegion()) continue;

		while (cell->getRegion() >= regions.size()) {
			regions.push_back({});
		}
			
		Point copy = cell->getPosition();
		regions.at(cell->getRegion()).addCell(copy.x, copy.y);
	}
	return regions;
}


void GameOfLife::World::checkHistory(vector<Patterns::Region> regions) {
	while (history.size() > 0 and history.top().nextAppearance <= gen) {
		Patterns::History check(history.top());
		history.pop();

		for (Patterns::Region region : regions) {
			if (region == check.shape) {
				pair<int, int> offset = check.shape.getSpacialDifference(region);
				if (offset.first == target.getXOffset() and offset.second == target.getYOffset()) match = true;
			}
		}
	}
}


void GameOfLife::World::addToHistory() {
	vector<Patterns::Region> regions = makeRegions();
	for (Patterns::Region region : regions) {
		if (region == target) {
			Patterns::History seen(region, gen + target.getPeriod());
			history.push(seen);
		}
	}
}
