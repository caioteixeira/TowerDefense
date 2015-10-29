#pragma once
#include "Tower.h"

class FrostTower : public Tower{
	DECL_ACTOR(FrostTower, Tower);
public:
	FrostTower(Game & game);
	void FrostEnemies();
private:
};
DECL_PTR(FrostTower);