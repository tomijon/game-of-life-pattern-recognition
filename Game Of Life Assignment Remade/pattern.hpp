#pragma once

#include <queue>
#include <string>
#include <functional>
#include <unordered_set>

using namespace std;

namespace Patterns {

	struct Node {
		int x;
		int y;

		bool operator==(const Node& other) const { return x == other.x and y == other.y; }
	};


	struct NodeHash {
		size_t operator()(const Node& node) const {
			return (static_cast<size_t>(node.x) << 32) ^ static_cast<size_t>(node.y);
		}
	};


	class Region {
	public:
		Region() {}
		Region(const Region& other) : minX(other.minX), minY(other.minY), nodes(other.nodes), size(other.size) {}
		Region(Region&& other) noexcept : minX(other.minX), minY(other.minY), nodes(other.nodes), size(other.size) {}

		void addCell(int x, int y) {
			nodes.insert({ x, y });

			if (x < minX) {
				minX = x;
				minY = y;
			}
			else if (x == minX and y < minY) {
				minY = y;
			}
		}

		unordered_set<Node, NodeHash> generateShape() const;

		pair<int, int> getSpacialDifference(const Region& other) const {
			return { minX - other.minX, minY - other.minY };
		}

		bool operator==(const Region& other) const {
			return generateShape() == other.generateShape();
		}

		Region& operator=(const Region& other) {
			minX = other.minX;
			minY = other.minY;
			size = other.size;
			nodes = other.nodes;
			return *this;
		}

		int getMinX() { return minX; }
		int getMinY() { return minY; }

		int size = 0;
	protected:
		unordered_set<Node, NodeHash> nodes;
		int minX = INT32_MAX;
		int minY = INT32_MAX;
	};


	class Pattern : public Region {
	public:
		Pattern() : Region(), period(0), xOffset(0), yOffset(0) {}
		Pattern(const Pattern& other) : period(other.period), xOffset(other.xOffset), yOffset(other.yOffset) {
			minX = other.minX;
			minY = other.minY;
			size = other.size;
			nodes = other.nodes;
		}
		Pattern(Pattern&& other) noexcept : period(other.period), xOffset(other.xOffset), yOffset(other.yOffset) {
			minX = other.minX;
			minY = other.minY;
			size = other.size;
			nodes = other.nodes;
		}

		void setPeriod(int period) { this->period = period; }
		int getPeriod() { return period; }

		void setOffset(int x, int y) {
			xOffset = x;
			yOffset = y;
		}

		int getXOffset() { return xOffset; }
		int getYOffset() { return yOffset; }

		Pattern& operator=(const Pattern& other) {
			period = other.period;
			xOffset = other.xOffset;
			yOffset = other.yOffset;
			nodes = other.nodes;
			minX = other.minX;
			minY = other.minY;
			size = other.size;
			return *this;
		}

		Pattern& operator=(Pattern&& other) noexcept {
			period = other.period;
			xOffset = other.xOffset;
			yOffset = other.yOffset;
			nodes = other.nodes;
			minX = other.minX;
			minY = other.minY;
			size = other.size;
			return *this;
		}

	private:
		int period;
		int xOffset;
		int yOffset;
	};


	struct History {
		History(Region shape, int next) : shape(shape), nextAppearance(next) {}

		History(const History& other) : shape(other.shape), nextAppearance(other.nextAppearance) {}

		Region shape;
		int nextAppearance;

		bool operator<(const History& other) const {
			return nextAppearance > other.nextAppearance;
		}

		void operator=(const History& other) {
			shape = other.shape;
			nextAppearance = other.nextAppearance;
		}

	};


	struct Target {
		Pattern* targets;
		int amount;
		int patternID;

		Target(const Target& other) : amount(other.amount), patternID(other.patternID) {
			targets = new Pattern[amount];
			for (int i = 0; i < amount; i++) {
				targets[i] = other.targets[i];
			}
		}

		Target() : targets(nullptr), amount(0), patternID(0) {}
		Target(Target&& other) noexcept : amount(other.amount), patternID(other.patternID), targets(other.targets) {
			other.targets = nullptr;
		}
		~Target() { if (targets != nullptr) delete[] targets; }

		int getXOffset(Region region) { return findMatch(region).getXOffset(); }
		int getYOffset(Region region) { return findMatch(region).getYOffset(); }
		int getPeriod() { return targets[0].getPeriod(); }
		Pattern findMatch(Region region) {
			for (int i = 0; i < amount; i++) {
				if (region == targets[i]) return targets[i];
			}
			return targets[0];
		}

		bool operator==(const Region& other) const {
			for (int i = 0; i < amount; i++) {
				if (other == targets[i]) return true;
			}
			return false;
		}

		Target& operator=(const Target& other) {
			amount = other.amount;
			patternID = other.patternID;
			targets = new Pattern[amount];
			for (int i = 0; i < amount; i++) {
				targets[i] = other.targets[i];
			}
			return *this;
		}

		Target& operator=(Target&& other) noexcept {
			amount = other.amount;
			patternID = other.patternID;
			targets = other.targets;
			other.targets = nullptr;
			return *this;
		}
	};

}