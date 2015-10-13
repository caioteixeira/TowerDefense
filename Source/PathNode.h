#pragma once
#include "Tile.h"
#include <vector>

struct PathNode{
	std::vector<PathNode *> adjacencyList;
	TilePtr tile;
	Vector2 gridPosition;
	PathNode * parent;
	float f; //Total cost
	float g; //Path Cost
	float h; //Admissable heuristic
	bool isBlocked;
};