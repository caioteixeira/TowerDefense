#pragma once
#include "PathNode.h"
#include <vector>

class NavWorld{
public:
	NavWorld();
	~NavWorld();
	//Initialize the navGrid using the physical world grid
	void Initialize(std::vector<std::vector<TilePtr>> mGrid);
	bool TryFindPath();
	void SetStartNode(int x, int y);
	void SetEndNode(int x, int y);
	PathNode * GetStartNode() { return startNode; }
	PathNode * GetEndNode() { return endNode;  }
	bool SetBlockedNode(Vector2 pos);
private:
	std::vector<std::vector<PathNode *>> mNavGrid;
	PathNode * startNode;
	PathNode * endNode;
	float ComputeG(PathNode * newParent);
	float ComputeH(PathNode * node);
	void CleanPathTextures();
	void UpdatePathTextures();
};