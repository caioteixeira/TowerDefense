#include "Enemy.h"
#include "Game.h"
#include "Tile.h"
#include "CannonBall.h"

IMPL_ACTOR(Enemy, Actor);

Enemy::Enemy(Game & game) : Actor(game){
	//Create the mesh
	mMeshComponent = MeshComponent::Create(*this);
	auto& assetCache = game.GetAssetCache();
	auto mesh = assetCache.Load<Mesh>("Meshes/Peasant.itpmesh2");
	mMeshComponent->SetMesh(mesh);

	//Create a Move component
	mNavComponent = NavComponent::Create(*this, Component::PreTick);
	mNavComponent->SetLinearSpeed(60.0f);
	mNavComponent->SetLinearAxis(1.0f);

	//Create a Sphere collision
	mColl = SphereCollision::Create(*this);
	mColl->RadiusFromMesh(mesh);
	mColl->SetScale(0.2f);

	//Audio stuff
	mAudio = AudioComponent::Create(*this);
	mFreezeSound = assetCache.Load<Sound>("Sounds/Freeze.wav");
	mDeathSound = assetCache.Load<Sound>("Sounds/WilhelmScream.wav");
}

void Enemy::BeginTouch(Actor & other){

	//If reaches the end
	if (other.IsAlive() && IsA<Tile>(other)){
		SetIsAlive(false);
		mGame.GetGameMode()->Damage(50);
	}

	//If shooted
	if (other.IsAlive() && IsA<CannonBall>(other)){
		other.SetIsAlive(false);
		mHealth--;
		if (mHealth <= 0){
			SetIsAlive(false);
			mAudio->PlaySound(mDeathSound);
			//Give money to the player
			mGame.GetGameMode()->AddMoney(15);
		}
	}
}

void Enemy::BeginPlay(){
	auto & enemySet = mGame.GetWorld().mEnemies;
	enemySet.insert(this);
}

void Enemy::EndPlay(){
	mGame.GetTime().ClearAllTimers(this);
	auto & enemySet = mGame.GetWorld().mEnemies;
	enemySet.erase(this);
}

void Enemy::Slow(){
	mNavComponent->SetLinearSpeed(mNavComponent->GetLinearSpeed() * 0.5f);
	mMeshComponent->SetTextureIndex(1);

	TimerHandle handle;
	mGame.GetTime().SetTimer(handle, this, &Enemy::UnSlow, 1.0f);

	mAudio->PlaySound(mFreezeSound);
}

void Enemy::UnSlow(){
	if (this->IsAlive()){
		mNavComponent->SetLinearSpeed(mNavComponent->GetLinearSpeed() * 2.0f);
		mMeshComponent->SetTextureIndex(0);
	}
}