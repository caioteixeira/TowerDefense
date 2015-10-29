#include "World.h"

World::World()
{

}

World::~World()
{

}

void World::AddActor(ActorPtr actor)
{
	mActors.emplace(actor);
}

void World::Tick(float deltaTime)
{
	// Tick a copy of the actor pointers, in case any actor adds more actors
	auto actors = mActors;
	for (auto& actor : actors)
	{
		actor->TickInternal(deltaTime);
	}

	// Remove any actors that are dead
	auto iter = mActors.begin();
	while (iter != mActors.end())
	{
		if (!(*iter)->IsAlive())
		{
			(*iter)->EndPlay();
			iter = mActors.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void World::RemoveAllActors()
{
	for (auto& actor : mActors)
	{
		actor->EndPlay();
	}
	mActors.clear();
}

std::vector<Enemy *> World::GetEnemiesInRange(Vector3 position, float radius){
	std::vector<Enemy *> vector;

	for (Enemy * enemy : mEnemies){
		Vector3 enemyPos = enemy->mPosition;
		float dist = Math::Sqrt((enemyPos.x - position.x)*(enemyPos.x - position.x) + (enemyPos.y - position.y)*(enemyPos.y - position.y));

		if (dist <= radius){
			vector.push_back(enemy);
		}
	}

	return vector;
}

Enemy* World::GetClosestEnemy(Vector3 position, float range){
	Enemy * closest = nullptr;
	float closestDist = range;

	for (Enemy * enemy : mEnemies){
		Vector3 enemyPos = enemy->GetPosition();
		float dist = Math::Sqrt((enemyPos.x - position.x)*(enemyPos.x - position.x) + (enemyPos.y - position.y)*(enemyPos.y - position.y));

		if (dist < closestDist){
			closest = enemy;
		}
	}

	return closest;
}
