#pragma once

#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <string>

#include "pattern.hpp"
#include "predefined_patterns.hpp"

using namespace std;

namespace GameOfLife {

	const int NEIGHBORS = 8;

	struct Point {
		Point() : x(0), y(0) {}
		Point(int x, int y) : x(x), y(y) {}
		Point(const Point& other) : x(other.x), y(other.y) {}

		int x;
		int y;

		bool operator==(const Point& other) const { return x == other.x and y == other.y; }
		Point operator+(const Point& other) const { return { x + other.x, y + other.y }; }
	};


	struct PointHash {
		size_t operator()(const Point& point) const { return (static_cast<size_t>(point.x) << 32) ^ static_cast<size_t>(point.y); }
	};


	const Point neighborVectors[8] =
	{
		{-1, -1}, {0, -1}, {1, -1}, 
		{-1, 0}, {1, 0},			
		{-1, 1}, {0, 1}, {1, 1}	
	};


	enum CellState {
		ALIVE,
		DEAD,
		INVALID
	};


	class Cell {
	public:
		Cell() { init(INVALID); }
		Cell(Point p, CellState newState) : location(p), state(newState), regionID(-1), sectionID(-1) {
			for (int n = 0; n < NEIGHBORS; n++) {
				setNeighbor(n, nullptr);
			}
		}
		Cell(const Cell& other) noexcept : location(other.location), regionID(other.regionID), sectionID(other.sectionID), state(other.state) {
			for (int n = 0; n < NEIGHBORS; n++) {
				setNeighbor(n, other.neighbors[n]);
			}
		}
		Cell(Cell&& other) noexcept : location(other.location), regionID(other.regionID), sectionID(other.sectionID), state(other.state) {
			for (int n = 0; n < NEIGHBORS; n++) {
				setNeighbor(n, other.neighbors[n]);
			}
		}

		inline void setNeighbor(int neighbor, Cell* cell) { neighbors[neighbor] = cell; }
		inline Cell* getNeighbor(int neighbor) { return neighbors[neighbor]; }

		inline void setRegion(int region) { regionID = region; }
		inline int getRegion() { return regionID; }
		inline bool hasRegion() { return regionID != -1; }

		inline void setSection(int section) { sectionID = section; }
		inline int getSection() { return sectionID; }
		inline bool hasSection() { return sectionID != -1; }

		inline void setState(CellState newState) { state = newState; }
		inline CellState getState() { return state; }
		inline bool isAlive() { return state == ALIVE; }
		inline bool isDead() { return state == DEAD; }
		inline bool isValid() { return state != INVALID; }
		
		inline Point getPosition() { return location; }

		void operator=(const Cell& other) noexcept {
			location = other.location;
			regionID = other.regionID;
			state = other.state;
			for (int n = 0; n < NEIGHBORS; n++) {
				setNeighbor(n, other.neighbors[n]);
			}
		}

		void operator=(Cell&& other) noexcept {
			location = other.location;
			regionID = other.regionID;
			state = other.state;
			for (int n = 0; n < NEIGHBORS; n++) {
				setNeighbor(n, other.neighbors[n]);
			}
		}

	private:
		Point location;
		Cell* neighbors[8];
		int regionID;
		int sectionID;
		CellState state;

		inline void init(CellState newState) {
			location = { 0, 0 };
			for (int n = 0; n < NEIGHBORS; n++) {
				setNeighbor(n, nullptr);
			}
			regionID = -1;
			sectionID = -1;
			setState(newState);
		}
	};


	class World {
	public:
		World() {}

		void setXRange(int low, int high) { lowX = low; highX = high; }
		void setYRange(int low, int high) { lowY = low; highY = high; }
		void setInitial(int amount) { initialActive = amount; }

		inline void setAliveCell(Point location) { cells[location] = new Cell(location, ALIVE); }
		inline void setDeadCell(Point location) { cells[location] = new Cell(location, DEAD); }
		inline void setInvalidCell(Point location) { cells[location] = new Cell(location, INVALID); }
		inline bool cellExists(Point location) { return cells.find(location) != cells.end(); }
		inline void searchFor(Base::BasePattern pattern) { target = Base::getPatterns(pattern); }
		inline int getWidth() { return highX - lowX; }
		inline int getHeight() { return highY - lowY; }

		void generate() {
			srand(seed);
			int active = 0;
			while (active < initialActive) {
				int x = rand() % (highX - lowX);
				int y = rand() % (highY - lowY);
				if (cellExists({ x, y })) continue;
				setAliveCell({ x, y });
				active++;
			}
			createNeighbors();
			assignRegions();
			assignSections();
			auto reg = makeRegions();
			addToHistory(reg);
			addToHistory(makeSections());
			gen++;
		}
		inline void setSeed(int seed) { this->seed = seed; }
		inline void setTargetGeneration(int target) { targetGeneration = target; }
		inline int getTargetGeneration() { return targetGeneration; }
		inline void run() { while (gen > -1 and gen < targetGeneration and not match) update(); }
		
		inline int getGen() { return gen; }

		void createNeighbors() {
			assignActiveNeighbors();
			assignDeadNeighbors();
		}

		string toString() {
			string output;
			for (int y = lowY; y < highY; y++) {
				for (int x = lowX; x < highX; x++) {
					output += ".";
					if (not cellExists({ x, y })) {
						output += " ";
						continue;
					}

					Cell* cell = cells[{x, y}];
					//if (cell->isAlive()) output += to_string(cell->getSection());
					//else output += " ";
					if (cell->isAlive()) output += "O";
					else output += " ";

					//else if (cell->isDead()) cout << ".";
					//else cout << "I";
				}
				output += ".\n";
			}
			return output;
		}

		void assignSections() {
			int section = 0;
			
			for (pair<Point, Cell*> cell : cells) {
				if (not cell.second->hasSection()) {
					fillSection(cell.second, section);
					section++;
				}
			}
		}

		void fillSection(Cell* cell, int section) {
			cell->setSection(section);
			for (int n = 0; n < NEIGHBORS; n++) {
				if (cell->getNeighbor(n) == nullptr) continue;
				if (cell->getNeighbor(n)->hasSection()) continue;

				if (cell->isAlive()) fillSection(cell->getNeighbor(n), section);
				else if (cell->isDead() and cell->getNeighbor(n)->isAlive()) fillSection(cell->getNeighbor(n), section);
			}
		}
	
		void assignRegions() {
			int region = 0;

			for (pair<Point, Cell*> cell : cells) {
				if (cell.second->isAlive() and not cell.second->hasRegion()) {
					fillRegion(cell.second, region);
					region++;
				}
			}
		}

		void addToHistory(vector<Patterns::Region> regions);

		vector<Patterns::Region> makeRegions();
		vector<Patterns::Region> makeSections();

		void fillRegion(Cell* cell, int region) {
			cell->setRegion(region);

			for (int n = 0; n < NEIGHBORS; n++) {
				if (cell->getNeighbor(n) == nullptr) continue;
				if (cell->getNeighbor(n)->hasRegion()) continue;

				if (cell->isAlive() and cell->getNeighbor(n)->isAlive()) {
					fillRegion(cell->getNeighbor(n), region);
				}
			}
		}


		void save(const string filename) const;
		void load(const string filename);

		void update();

		bool found() { return match; }

		int gen = -1;
	private:
		unordered_map<Point, Cell*, PointHash> cells;
		priority_queue<Patterns::History> history;

		int initialActive = 0;
		int targetGeneration = 0;
		int lowX = 0;		
		int highX = 20;
		int lowY = 0;
		int highY = 20;
		bool match = false;
		int seed = 0;

		Patterns::Target target;

		void clearCells() {
			for (auto cell : cells) {
				delete cell.second;
			}
			cells.clear();
		}

		void assignActiveNeighbors() {
			vector<Cell*> aliveCells;

			for (pair<Point, Cell*> cell : cells) {
				if (cell.second->isAlive()) aliveCells.push_back(cell.second);
			}

			for (Cell* alive : aliveCells) {
				for (int n = 0; n < NEIGHBORS; n++) {
					Point newPos = alive->getPosition() + neighborVectors[n];

					if (not cellExists(newPos)) setDeadCell(newPos);
					alive->setNeighbor(n, cells[newPos]);
				}
			}
		}

		void assignDeadNeighbors() {
			for (pair<Point, Cell*> cell : cells) {
				if (cell.second->isDead()) {
					for (int n = 0; n < NEIGHBORS; n++) {
						Point newPos = cell.second->getPosition() + neighborVectors[n];
						if (not cellExists(newPos)) cell.second->setNeighbor(n, nullptr);
						else cell.second->setNeighbor(n, cells[newPos]);
					}
				}
			}
		}

		void checkHistory(vector<Patterns::Region> regions);

	};
}