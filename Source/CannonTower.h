#pragma once
#include "Tower.h"
#include "AudioComponent.h"

class CannonTower : public Tower{
	DECL_ACTOR(CannonTower, Tower);
public:
	CannonTower(Game & game);
	void Fire();
	AudioComponentPtr GetAudio(){ return mAudio; };
private:
	ActorPtr mCannon;
	AudioComponentPtr mAudio;
	SoundPtr mShottingSound;
};
DECL_PTR(CannonTower);