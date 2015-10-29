// World.h
// All actors in the game world should either
// directly or indirectly (by parent) be
// controlled by World

#pragma once
#include <memory>
#include <unordered_set>
#include "Actor.h"
#include "Enemy.h"
#include <vector>

class World
{
public:
	World();
	~World();

	void AddActor(ActorPtr actor);

	void Tick(float deltaTime);
	
	void RemoveAllActors();

	std::vector<Enemy *> GetEnemiesInRange(Vector3 position, float radius);
	Enemy * GetClosestEnemy(Vector3 position, float range = 150.0f);

	std::unordered_set<Enemy *> mEnemies;
private:
	std::unordered_set<ActorPtr> mActors;
	
};
