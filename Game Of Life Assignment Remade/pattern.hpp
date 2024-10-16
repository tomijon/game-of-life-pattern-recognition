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
		Region() : minX(INT32_MAX), minY(INT32_MAX) {}

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

		int getMinX() { return minX; }
		int getMinY() { return minY; }

	protected:
		unordered_set<Node, NodeHash> nodes;
		int minX;
		int minY;
	};


	class Pattern : public Region {
	public:
		Pattern() : Region(), period(0), xOffset(0), yOffset(0) {}

		void setPeriod(int period) { this->period = period; }
		int getPeriod() { return period; }

		void setOffset(int x, int y) {
			xOffset = x;
			yOffset = y;
		}

		int getXOffset() { return xOffset; }
		int getYOffset() { return yOffset; }

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
}