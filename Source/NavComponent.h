#pragma once
#include "MoveComponent.h"
#include "PathNode.h"

class NavComponent : public MoveComponent{
	DECL_COMPONENT(NavComponent, MoveComponent);
public:
	NavComponent(Actor & owner);
	void Tick(float deltaTime) override;
	void FollowPath(PathNode * start, PathNode * end);
private:
	PathNode * mNext;
	PathNode * mEnd;
};

DECL_PTR(NavComponent);