#include "Tower.h"
#include "Game.h"
#include "MeshComponent.h"

IMPL_ACTOR(Tower, Actor);

Tower::Tower(Game & game) : Actor (game){
	//Get Asset Cache
	auto& assetCache = game.GetAssetCache();

	//Create a mesh component
	auto meshComponent = MeshComponent::Create(*this);
	auto mesh = assetCache.Load<Mesh>("Meshes/TowerBase.itpmesh2");
	meshComponent->SetMesh(mesh);
}