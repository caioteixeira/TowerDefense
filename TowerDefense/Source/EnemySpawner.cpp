#include "EnemySpawner.h"
#include "Game.h"
#include "Enemy.h"

IMPL_ACTOR(EnemySpawner, Actor);

EnemySpawner::EnemySpawner(Game & game) : Actor(game){

}

void EnemySpawner::BeginPlay(){

	//Initial wave
	TimerHandle handle;
	mGame.GetTime().SetTimer(handle, this, &EnemySpawner::StartWave, 5.0f);
}

void EnemySpawner::StartWave(){
	mNextWave = mNextWave + 5;
	mActualWaveCounter = mNextWave;

	TimerHandle handle;
	mGame.GetTime().SetTimer(handle, this, &EnemySpawner::WaveSpawn, 0.1f);
}

void EnemySpawner::WaveSpawn(){
	mActualWaveCounter--;
	Spawn();
	if (mActualWaveCounter <= 0){
		//Schedule new Wave
		TimerHandle handle;
		mGame.GetTime().SetTimer(handle, this, &EnemySpawner::StartWave, 5.0f);
	}
	else {
		TimerHandle handle;
		mGame.GetTime().SetTimer(handle, this, &EnemySpawner::WaveSpawn, 1.0f);
	}
}

void EnemySpawner::Spawn(){
	auto enemy = Enemy::Spawn(mGame);
	//Arbitrary position
	enemy->SetPosition(Vector3(-425, 0, 0));
	enemy->GetNavComponent()->FollowPath(mGame.GetNavWorld().GetStartNode(), mGame.GetNavWorld().GetEndNode());
}