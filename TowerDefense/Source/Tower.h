#pragma once
#include "Actor.h"

class Tower : public Actor{
	DECL_ACTOR(Tower, Actor);
public:
	Tower(Game & game);
private:
};
DECL_PTR(Tower);