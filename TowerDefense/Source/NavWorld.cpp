#include "NavWorld.h"
#include <unordered_set>

NavWorld::NavWorld(){

}

NavWorld::~NavWorld(){
	//Dealocate the PathNode pointers
	for (unsigned int i = 0; i < mNavGrid.size(); i++){
		auto& row = mNavGrid[i];
		for (int j = 0; j < row.size(); j++){
			delete mNavGrid[i][j];
		}
	}
}

void NavWorld::SetStartNode(int x, int y){
	if (x < mNavGrid.size()){
		if (y < (int) (mNavGrid[x].size())){
			startNode = mNavGrid[x][y];
		}
	}
}

void NavWorld::SetEndNode(int x, int y){
	if (x < mNavGrid.size()){
		if (y < (int)(mNavGrid[x].size())){
			endNode = mNavGrid[x][y];
		}
	}
}

bool NavWorld::SetBlockedNode(Vector2 pos){
	int x = pos.x;
	int y = pos.y;
	
	if (x < mNavGrid.size()){
		if (y < (int)(mNavGrid[x].size())){
			mNavGrid[x][y]->isBlocked = true;
			if (TryFindPath()){
				return true;
			}
			else {
				mNavGrid[x][y]->isBlocked = false;
				TryFindPath();
				return false;
			}
		}
	}
	return false;
}

void NavWorld::Initialize(std::vector<std::vector<TilePtr>> mGrid){
	//Initialize the grid
	mNavGrid.resize(mGrid.size());
	for (unsigned int i = 0; i < mNavGrid.size(); i++){
		auto& row = mNavGrid[i];
		for (unsigned int j = 0; j < mGrid[i].size(); j++){
			PathNode * node = new PathNode();
			
			node->gridPosition = Vector2(i,j);
			node->tile = mGrid[i][j];
			node->isBlocked = false;
			node->parent = nullptr;
			node->g = 0.0f;
			node->h = 0.0f;
			node->f = node->g + node->h;
			row.push_back(node);
		}
	}

	//Initialize the adjacency lists
	for (int i = 0; i < mNavGrid.size(); i++){
		auto& row = mNavGrid[i];
		for (int j = 0; j < row.size(); j++){
			PathNode * node = mNavGrid[i][j];

			if (i - 1 >= 0){
				node->adjacencyList.push_back(mNavGrid[i - 1][j]);
			}
			if (i + 1 < mNavGrid.size()){
				node->adjacencyList.push_back(mNavGrid[i + 1][j]);
			}
			if (j - 1 >= 0){
				node->adjacencyList.push_back(mNavGrid[i][j - 1]);
			}
			if (j + 1 < mNavGrid[i].size()){
				node->adjacencyList.push_back(mNavGrid[i][j + 1]);
			}
		}
	}
}

//A* implementation
bool NavWorld::TryFindPath(){
	CleanPathTextures();

	PathNode * currentNode = endNode;
	currentNode->h = ComputeH(currentNode);
	currentNode->g = 1.0f;
	currentNode->f = currentNode->h + currentNode->g;

	std::unordered_set<PathNode *> openSet;
	std::unordered_set<PathNode *> closedSet;

	closedSet.insert(currentNode);

	do{
		//foreach n adjacent node
		for (PathNode * n : currentNode->adjacencyList){
			//closed set contains n
			if (closedSet.count(n) > 0){
				continue;
			}
			else if (openSet.count(n) > 0){
				//Recompute g
				float new_g = ComputeG(currentNode);
				if (new_g < n->g){
					n->parent = currentNode;
					n->g = new_g;
					n->f = n->g + n->h;
				}
			}
			else if(!n->isBlocked){
				n->parent = currentNode;
				n->g = ComputeG(currentNode);
				n->h = ComputeH(n);
				n->f = n->g + n->h;
				openSet.insert(n);
			}
		}

		if (openSet.size() == 0){
			break;
		}

		//Find the node with lowest f in closed set
		auto iter = openSet.begin();
		if (iter == openSet.end()){
			continue;
		}
		currentNode = *iter;
		for (; iter != openSet.end(); iter++){
			PathNode * n = *iter;
			if (n->f < currentNode->f){
				currentNode = n;
			}
		}

		//update sets
		closedSet.insert(currentNode);
		openSet.erase(currentNode);
	} while (currentNode != startNode);

	if (currentNode == startNode){
		UpdatePathTextures();
		return true;
	}
	return false;
}

float NavWorld::ComputeH(PathNode * node){
	if (node == nullptr)
		return 0.0f;
	
	//Calculate Manhatan distance
	float dx = node->gridPosition.x - startNode->gridPosition.x;
	float dy = node->gridPosition.y - startNode->gridPosition.y;
	return dx + dy;
}

float NavWorld::ComputeG(PathNode * newParent){
	if (newParent == nullptr)
		return 0.0f;

	return ComputeG(newParent->parent) + 1.0f;
}

void NavWorld::CleanPathTextures(){
	for (int i = 0; i < mNavGrid.size(); i++){
		auto& row = mNavGrid[i];
		for (int j = 0; j < row.size(); j++){
			row[j]->tile->SetOnPath(false);
		}
	}
}

void NavWorld::UpdatePathTextures(){
	PathNode * current = startNode;
	while (current != nullptr){
		current->tile->SetOnPath(true);
		current = current->parent;
	}
}
