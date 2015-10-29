#include "NavComponent.h"
#include "Actor.h"

IMPL_COMPONENT(NavComponent, MoveComponent);

NavComponent::NavComponent(Actor & owner) : MoveComponent(owner){

}

void NavComponent::Tick(float deltaTime){
	//Check if the enemy is near the next node
	Vector3 nodeDir = mOwner.GetPosition() - mNext->tile->GetPosition();
	if (nodeDir.Length() < 1.0f){
		if (mNext->parent){
			//Turn the enemy to the next node
			mNext = mNext->parent;
			nodeDir = mNext->tile->GetPosition() - mOwner.GetPosition();
			nodeDir.Normalize();
			float angle = Math::Acos(Dot(nodeDir, Vector3::UnitX));
			float crossZ = Cross(Vector3::UnitX, nodeDir).z;
			if (crossZ < 0.0f){
				angle *= -1.0f;
			}
			mOwner.SetRotation(angle);
		}
	}


	MoveComponent::Tick(deltaTime);
}

void NavComponent::FollowPath(PathNode * start, PathNode * end){
	mNext = start->parent;
	Vector3 nodeDir = mNext->tile->GetPosition() - mOwner.GetPosition();
	nodeDir.Normalize();
	float angle = Math::Acos(Dot(nodeDir, Vector3::UnitX));
	float crossZ = Cross(Vector3::UnitX, nodeDir).z;
	if (crossZ < 0.0f){
		angle *= -1.0f;
	}
	mOwner.SetRotation(angle);
	mEnd = end;
}