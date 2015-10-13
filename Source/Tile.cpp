#include "Tile.h"
#include "Game.h"
#include "SphereCollision.h"

IMPL_ACTOR(Tile, Actor);

Tile::Tile(Game & game) : Actor(game){
	//Get the asset cache
	auto& assetCache = game.GetAssetCache();

	//Create a Mesh Component
	mMeshComponent = MeshComponent::Create(*this);
	mMesh = assetCache.Load<Mesh>("Meshes/Tile.itpmesh2");
	mMeshComponent->SetMesh(mMesh);

	//Start Tile Status
	SetTileStatus(DEFAULT);

	mTower = nullptr;
}

void Tile::SetTileStatus(TileStatus status){
	if (status == RED){
		auto coll = SphereCollision::Create(*this);
		coll->RadiusFromMesh(mMesh);
	}


	mStatus = status;
	mMeshComponent->SetTextureIndex((int)status);
}

void Tile::SetOnPath(bool IsOnPath){
	if (IsOnPath){
		if ((int)mStatus < 4){
			mStatus = (TileStatus)((int)mStatus + 4);
		}
	}
	else {
		if ((int)mStatus > 3){
			mStatus = (TileStatus)((int)mStatus - 4);
		}
	}

	mMeshComponent->SetTextureIndex((int)mStatus);
}