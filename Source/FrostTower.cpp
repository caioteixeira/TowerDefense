#include "FrostTower.h"
#include "Game.h"
#include "MeshComponent.h"

IMPL_ACTOR(FrostTower, Tower);

FrostTower::FrostTower(Game & game) : Tower(game){
	//Get Asset Cache
	auto& assetCache = game.GetAssetCache();

	//Create a mesh component
	auto meshComponent = MeshComponent::Create(*this);
	auto mesh = assetCache.Load<Mesh>("Meshes/Frost.itpmesh2");
	meshComponent->SetMesh(mesh);

	//Set Frost timer
	TimerHandle handle;
	mGame.GetTime().SetTimer(handle, this, &FrostTower::FrostEnemies, 2.0f, true);
}

void FrostTower::FrostEnemies(){
	//Get the near enemies vector
	std::vector<Enemy *> enemies = mGame.GetWorld().GetEnemiesInRange(GetWorldTransform().GetTranslation(), 100.0f);

	for (Enemy * enemy : enemies){
		enemy->Slow();
	}
}