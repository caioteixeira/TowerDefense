#pragma once
#include "Actor.h"

class EnemySpawner : public Actor{
	DECL_ACTOR(EnemySpawner, Actor);
public:
	EnemySpawner(Game & game);
	void BeginPlay() override;
	void StartWave();
	void WaveSpawn();
private:
	void Spawn();
	int mActualWaveCounter = 0;
	int mNextWave = 0;
};

DECL_PTR(EnemySpawner);