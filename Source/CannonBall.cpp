#include "CannonBall.h"
#include "Game.h"

IMPL_ACTOR(CannonBall, Actor);

CannonBall::CannonBall(Game & game) : Actor(game){
	//Create the mesh
	mMeshComponent = MeshComponent::Create(*this);
	auto& assetCache = game.GetAssetCache();
	auto mesh = assetCache.Load<Mesh>("Meshes/Cannonball.itpmesh2");
	mMeshComponent->SetMesh(mesh);

	//Create a Move component
	mMoveComponent = MoveComponent::Create(*this, Component::PreTick);
	mMoveComponent->SetLinearSpeed(300.0f);
	mMoveComponent->SetLinearAxis(1.0f);

	//Create a Sphere collision
	mColl = SphereCollision::Create(*this);
	mColl->RadiusFromMesh(mesh);
	//mColl->SetScale(0.2f);


	//Set Frost timer
	TimerHandle handle;
	mGame.GetTime().SetTimer(handle, this, &CannonBall::deSpawn, 3.0f);
}

void CannonBall::deSpawn(){
	SetIsAlive(false);
}