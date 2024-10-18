#include <filesystem>
#include <fstream>

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
	assignSections();
	vector<Patterns::Region> regions = makeRegions();
	vector<Patterns::Region> sections = makeSections();
	addToHistory(regions);
	addToHistory(sections);
	checkHistory(regions);
	checkHistory(sections);
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


vector<Patterns::Region> GameOfLife::World::makeSections() {
	vector<Patterns::Region> sections;

	for (pair<Point, Cell*> map : cells) {
		Cell* cell = map.second;
		if (not cell->hasSection()) continue;
		if (not cell->isAlive()) continue;

		while (cell->getSection() >= sections.size()) {
			sections.push_back({});
		}
			
		Point copy = cell->getPosition();
		sections.at(cell->getSection()).addCell(copy.x, copy.y);
	}
	return sections;
}


void GameOfLife::World::checkHistory(vector<Patterns::Region> Regions) {
	vector<Patterns::History> checked;

	while (history.size() > 0 and history.top().nextAppearance <= gen) {
		Patterns::History check(history.top());
		history.pop();

		for (Patterns::Region region : Regions) {
			if (region == check.shape) {
				if (region.getMinX() < 0 or region.getMinY() < 0 or region.getMinX() > getWidth() - check.shape.size - 1 or region.getMinY() > getHeight() - check.shape.size - 1) continue;
				pair<int, int> offset = check.shape.getSpacialDifference(region);
				if (offset.first == target.getXOffset() and offset.second == target.getYOffset()) match = true;
			}
		}

		if (not match) {
			checked.push_back(check);
		}
	}
	for (Patterns::History readd : checked) {
		history.push(readd);
	}
}


void GameOfLife::World::addToHistory(vector<Patterns::Region> regions) {
	for (Patterns::Region region : regions) {
		if (region == target) {
			Patterns::History seen(region, gen + target.getPeriod());
			history.push(seen);
		}
	}
}


void GameOfLife::World::save(const string name) const {
	filesystem::path filename(name);

	if (filesystem::exists(filename)) throw runtime_error("File with name already exists");

	ofstream save(filename);
	int width = highX - lowX;
	int height = highY - lowY;
	save.write(reinterpret_cast<const char*>(&width), 4);
	save.write(reinterpret_cast<const char*>(&height), 4);
	save.write(reinterpret_cast<const char*>(&initialActive), 4);
	save.write(reinterpret_cast<const char*>(&targetGeneration), 4);
	save.write(reinterpret_cast<const char*>(&seed), 4);
	save.write(reinterpret_cast<const char*>(&target.patternID), 4);
	save.close();
}


void GameOfLife::World::load(const string name) {
	filesystem::path filename(name);

	if (not filesystem::exists(filename)) throw runtime_error("File does not exist");

	ifstream load(filename);
	int patternID;
	int* assign[6] = { &highX, &highY, &initialActive, &targetGeneration, &seed, &patternID};
	char readInt[4];
	for (int i = 0; i < 6; i++) {
		load.read(readInt, 4);
		(*assign[i]) = *(reinterpret_cast<int*>(readInt));
	}
	Target x(Base::getPatterns(Base::BasePattern(patternID)));
	target = std::move(x);
}
