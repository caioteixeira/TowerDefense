#pragma once
#include "DrawComponent.h"
#include "Mesh.h"

class MeshComponent : public DrawComponent
{
	DECL_COMPONENT(MeshComponent, DrawComponent);
public:
	MeshComponent(Actor& owner);
	void Draw(class Renderer& render) override;
	MeshPtr GetMesh(){ return mMesh; };
	void SetMesh(MeshPtr mesh){ mMesh = mesh; };
	void SetTextureIndex(int index) { mTextureIndex = index; };
private:
	MeshPtr mMesh;
	int mTextureIndex = 0;
};

DECL_PTR(MeshComponent);