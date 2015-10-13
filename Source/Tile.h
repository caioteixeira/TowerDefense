#pragma once
#include "Actor.h"
#include "MeshComponent.h"
#include "Tower.h"

enum TileStatus{
	DEFAULT = 0,
	SELECTED = 1,
	GREEN = 2,
	RED = 3,
	DEFAULT_ONPATH = 4,
	SELECTED_ONPATH = 5,
	GREEN_ONPATH = 6,
	RED_ONPATH = 7
};


class Tile : public Actor{
	DECL_ACTOR(Tile, Actor);
public:
	Tile(Game & game);
	MeshComponentPtr GetMeshComponent(){ return mMeshComponent; }
	void SetTileStatus(TileStatus status);
	TileStatus GetTileStatus() { return mStatus; }
	ActorPtr GetTower() { return mTower; }
	void SetTower(ActorPtr tower) { mTower = tower; }
	void SetOnPath(bool isOnPath);
	Vector2 mPos;
private:
	MeshComponentPtr mMeshComponent;
	TileStatus mStatus;
	MeshPtr mMesh;
	ActorPtr mTower;
};

DECL_PTR(Tile);