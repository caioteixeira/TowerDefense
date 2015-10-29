#pragma once
#include "Tile.h"
#include <vector>
#include "AudioComponent.h"
#include "EnemySpawner.h"
#include "HUD.h"

class GameMode : public Actor{
	DECL_ACTOR(GameMode, Actor);

public:
	GameMode(Game & game);
	void BeginPlay() override;
	void SelectTile();
	void BuildCannon();
	void BuildFrost();
	void AddMoney(int value) { mMoney += value; };
	void Damage(int value);
	int GetMoney() { return mMoney; };
	int GetHealth() { return mHealth; };
	void SetErrorMessage(std::string message) { mHUD->SetErrorMessage(message); }
	AudioComponentPtr GetAudio(){ return mAudio; };
private:
	int mHealth;
	int mMoney;
	int mFreezeTowerCost;
	int mCannonTowerCost;
	std::vector<std::vector<TilePtr>> mGrid;
	TilePtr mSelectedTile;
	SoundPtr mBuildingSound;
	SoundPtr mErrorSound;
	AudioComponentPtr mAudio;
	EnemySpawnerPtr mSpawner;
	HUDPtr mHUD;
};
DECL_PTR(GameMode);