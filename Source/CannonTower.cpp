#include "CannonTower.h"
#include "Game.h"
#include "MeshComponent.h"
#include "Enemy.h"
#include "CannonBall.h"

IMPL_ACTOR(CannonTower, Tower);

CannonTower::CannonTower(Game & game) : Tower(game){
	//Get Asset Cache
	auto& assetCache = game.GetAssetCache();

	//Create the child
	mCannon = Actor::SpawnAttached(*this);

	//Create a mesh component
	auto meshComponent = MeshComponent::Create(*mCannon);
	auto mesh = assetCache.Load<Mesh>("Meshes/Cannon.itpmesh2");
	meshComponent->SetMesh(mesh);

	//Set the fire timer
	TimerHandle handle;
	mGame.GetTime().SetTimer(handle, this, &CannonTower::Fire, 1.0f, true);

	//Set shotting sound
	mAudio = AudioComponent::Create(*this);
	mShottingSound = assetCache.Load<Sound>("Sounds/CannonFire.wav");
}

void CannonTower::Fire(){
	//Get closest enemy
	Enemy * enemy = mGame.GetWorld().GetClosestEnemy(GetWorldTransform().GetTranslation());
	if (enemy == nullptr)
		return;

	//Turn to enemy direction
	SetRotation(0);
	Vector3 enemyDir = enemy->GetPosition() - GetWorldTransform().GetTranslation();
	enemyDir.Normalize();
	Vector3 towerPos = GetWorldTransform().GetTranslation();
	float angle = Math::Acos(Dot(enemyDir, Vector3::UnitX));
	float crossZ = Cross(Vector3::UnitX, enemyDir).z;
	if (crossZ < 0.0f){
		angle *= -1.0f;
	}
	SetRotation(angle);

	//Fire the ball
	auto ball = CannonBall::Spawn(mGame);
	ball->SetPosition(GetWorldTransform().GetTranslation());
	ball->SetRotation(angle);

	//Trigger the sound
	mAudio->PlaySound(mShottingSound);
}