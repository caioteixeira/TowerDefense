#pragma once
#include "Actor.h"
#include "NavComponent.h"
#include "SphereCollision.h"
#include "MeshComponent.h"
#include "AudioComponent.h"

class Enemy : public Actor{
	DECL_ACTOR(Enemy, Actor);
public:
	Enemy(Game & game);
	NavComponentPtr GetNavComponent() { return mNavComponent; }
	MeshComponentPtr GetMeshComponent() { return mMeshComponent; }
	AudioComponentPtr GetAudio(){ return mAudio; };
	void BeginTouch(Actor & other) override;
	void BeginPlay() override;
	void EndPlay() override;
	void Slow();
	void UnSlow();
private:
	NavComponentPtr mNavComponent;
	SphereCollisionPtr mColl;
	MeshComponentPtr mMeshComponent;
	AudioComponentPtr mAudio;
	int mHealth = 3;
	SoundPtr mFreezeSound;
	SoundPtr mDeathSound;
};
DECL_PTR(Enemy);