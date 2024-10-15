#pragma once

#include <queue>
#include <string>
#include <functional>
#include <unordered_map>

using namespace std;

namespace Patterns {

	struct Edge {
		int x1;
		int y1;
		int x2;
		int y2;

		bool operator>(const Edge& other) const {
			if (x1 > other.x1) return true;
			if (y1 > other.y1) return true;
			if (x2 > other.x2) return true;
			if (y2 > other.y2) return true;
			return false;
		}

		string toString() {
			return "(" + to_string(x1) + "," + to_string(y1) + "->" + to_string(x2) + "," + to_string(y2) + ")";
		}
	};

	struct CompareEdges {
		bool operator()(const Edge& first, const Edge& second) { return first > second; }
	};


	const unordered_map<Pattern, Pattern, PatternHash> patterns;
	


	class Pattern {
	public:
		void addEdge(Edge edge) { 
			if (edge.x1 < minX) {
				minX = edge.x1;
				minY = edge.y1;
			}

			if (edge.x1 == minX and edge.y1 < minY) {
				minY = edge.y1;
			}

			edges.push_back(edge);
		}

		string toString() const {
			priority_queue<Edge> sorted;
			string result = "";

			for (Edge edge : edges) {
				Edge copy = { edge.x1 - minX, edge.y1 - minY, edge.x2 - minX, edge.y2 - minY };
				sorted.push(copy);
			}

			while (not sorted.empty()) {
				Edge current = sorted.top();
				sorted.pop();
				result += current.toString();
			}
			return result;
		}

		bool shapeMatches(const Pattern& other) const {
			return toString() == other.toString();
		}

		bool positionMatches(const Pattern& other) const {
			return minX == other.minX and minY == other.minY;
		}

	private:
		int minX = INT32_MAX;
		int minY = INT32_MAX;
		vector<Edge> edges;
	};


	struct PatternHash {
		size_t operator()(const Pattern& other) const {
			hash<string> function;
			return function(other.toString());
		}
	};


}