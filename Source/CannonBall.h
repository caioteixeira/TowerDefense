#pragma once
#include "Actor.h"
#include "MoveComponent.h"
#include "SphereCollision.h"
#include "MeshComponent.h"

class CannonBall : public Actor{
	DECL_ACTOR(CannonBall, Actor);
public:
	CannonBall(Game & game);
	MoveComponentPtr GetMoveComponent() { return mMoveComponent; }
	MeshComponentPtr GetMeshComponent() { return mMeshComponent; }
	void deSpawn();
private:
	MoveComponentPtr mMoveComponent;
	SphereCollisionPtr mColl;
	MeshComponentPtr mMeshComponent;
};