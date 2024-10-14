#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>

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
		Cell(Point p, CellState newState) : location(p), state(newState), regionID(-1) {
			for (int n = 0; n < NEIGHBORS; n++) {
				setNeighbor(n, nullptr);
			}
		}
		Cell(const Cell& other) noexcept : location(other.location), regionID(other.regionID), state(other.state) {
			for (int n = 0; n < NEIGHBORS; n++) {
				setNeighbor(n, other.neighbors[n]);
			}
		}
		Cell(Cell&& other) noexcept : location(other.location), regionID(other.regionID), state(other.state) {
			for (int n = 0; n < NEIGHBORS; n++) {
				setNeighbor(n, other.neighbors[n]);
			}
		}

		inline void setNeighbor(int neighbor, Cell* cell) { neighbors[neighbor] = cell; }
		inline Cell* getNeighbor(int neighbor) { return neighbors[neighbor]; }

		inline void setRegion(int region) { regionID = region; }
		inline int getRegion() { return regionID; }
		inline bool hasRegion() { return regionID != -1; }

		inline void setState(CellState newState) { state = newState; }
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
		CellState state;

		inline void init(CellState newState) {
			location = { 0, 0 };
			for (int n = 0; n < NEIGHBORS; n++) {
				setNeighbor(n, nullptr);
			}
			regionID = -1;
			setState(newState);
		}
	};


	class World {
	public:
		World() {}

		void setAliveCell(Point location) { cells[location] = new Cell(location, ALIVE); }
		void setDeadCell(Point location) { cells[location] = new Cell(location, DEAD); }
		void setInvalidCell(Point location) { cells[location] = new Cell(location, INVALID); }
		bool cellExists(Point location) { return cells.find(location) != cells.end(); }

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
					//cout << cell->getRegion();
					if (cell->isAlive()) output += "O";
					else output += " ";


					//else if (cell->isDead()) cout << ".";
					//else cout << "I";
				}
				output += ".\n";
			}
			return output;
		}

		void assignRegions() {
			int region = 0;
			
			for (pair<Point, Cell*> cell : cells) {
				if (not cell.second->hasRegion()) {
					cell.second->setRegion(region);
					fillRegion(cell.second, region);
					region++;
				}
			}
		}

		void fillRegion(Cell* cell, int region) {
			for (int n = 0; n < NEIGHBORS; n++) {
				if (cell->getNeighbor(n) and not cell->getNeighbor(n)->hasRegion()) {
					cell->getNeighbor(n)->setRegion(region);
					fillRegion(cell->getNeighbor(n), region);
				}
			}
		}

		void update() {
			unordered_set<Point, PointHash> newAliveLocations;

			for (auto map : cells) {
				Cell* cell = map.second;

				if (not cell->isValid()) continue;

				int alive = 0;
				for (int n = 0; n < NEIGHBORS; n++) {
					if (cell->getNeighbor(n)->isAlive()) alive++;
				}
				if (alive == 3) newAliveLocations.insert(cell->getPosition());
				else if (alive == 2 and cell->isAlive()) newAliveLocations.insert(cell->getPosition());
			}

			for (auto cell : cells) {
				delete cell.second;
			}
			cells.clear();

			for (Point p : newAliveLocations) {
				setAliveCell(p);
			}
			createNeighbors();
		}

	private:
		unordered_map<Point, Cell*, PointHash> cells;

		int lowX = 0;		
		int highX = 30;		
		int lowY = 0;
		int highY = 30;

		void assignActiveNeighbors() {
			vector<Cell*> aliveCells;

			for (pair<Point, Cell*> cell : cells) {
				if (cell.second->isAlive()) aliveCells.push_back(cell.second);
			}

			for (Cell* alive : aliveCells) {
				for (int n = 0; n < NEIGHBORS; n++) {
					Point newPos = alive->getPosition() + neighborVectors[n];

					if (not cellExists(newPos)) {
						setDeadCell(newPos);
					}
					alive->setNeighbor(n, cells[newPos]);
				}
			}
		}

		void assignDeadNeighbors() {
			vector<Cell*> deadCells;

			for (pair<Point, Cell*> cell : cells) {
				if (cell.second->isDead()) deadCells.push_back(cell.second);
			}

			for (Cell* dead : deadCells) {
				for (int n = 0; n < NEIGHBORS; n++) {
					Point newPos = dead->getPosition() + neighborVectors[n];
					if (not cellExists(newPos)) {
						setInvalidCell(newPos);
					}
					dead->setNeighbor(n, cells[newPos]);
				}
			}
		}
	};
}