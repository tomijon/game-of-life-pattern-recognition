#include "pattern.hpp"

using namespace Patterns;

unordered_set<Node, NodeHash> Region::generateShape() const {
	unordered_set<Node, NodeHash> shifted;

	for (Node node : nodes) {
		node.x -= minX;
		node.y -= minY;
		shifted.insert(node);
	}
	return shifted;
}
