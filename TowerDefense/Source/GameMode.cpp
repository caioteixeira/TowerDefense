#include "GameMode.h"
#include "Game.h"
#include <vector>
#include "CannonTower.h"
#include "FrostTower.h"

IMPL_ACTOR(GameMode, Actor);

GameMode::GameMode(Game & game) : Actor(game){
	mSelectedTile = nullptr;
	auto& assetCache = mGame.GetAssetCache();

	mAudio = AudioComponent::Create(*this);
	mBuildingSound = assetCache.Load<Sound>("Sounds/Building.wav");
	mErrorSound = assetCache.Load<Sound>("Sounds/ErrorSound.wav");
}

void GameMode::BeginPlay(){
	//Initialize values
	mHealth = 200;
	mMoney = 200;
	mFreezeTowerCost = 75;
	mCannonTowerCost = 50;

	//Initialize the grid
	mGrid.resize(9);
	for (int i = 0; i < 9; i++){
		auto& row = mGrid[i];
		//row.resize(18);
		for (int j = 0; j < 18; j++){
			auto& tile = Tile::Spawn(mGame);

			float x = -425 + 50.0f * j;
			float y = 200 - 50.0f * i;
			float z = 0.0f;
			
			tile->SetPosition(Vector3(x,y,z));
			tile->mPos = Vector2(i, j);
			row.push_back(tile);
		}
	}

	//Set initial green and tiles
	mGrid[3][0]->SetTileStatus(GREEN);
	mGrid[4][0]->SetTileStatus(GREEN);
	mGrid[5][0]->SetTileStatus(GREEN);
	mGrid[4][1]->SetTileStatus(GREEN);


	//Set the red tile
	mGrid[4][17]->SetTileStatus(RED);

	//Initialize the navWorld
	NavWorld& navWorld = mGame.GetNavWorld();
	navWorld.Initialize(mGrid);
	navWorld.SetStartNode(4, 0);
	navWorld.SetEndNode(4, 17);
	navWorld.TryFindPath();

	//Bind selection
	mGame.GetInput().BindAction("Select", IE_Pressed, this, &GameMode::SelectTile);
	mGame.GetInput().BindAction("Cannon", IE_Pressed, this, &GameMode::BuildCannon);
	mGame.GetInput().BindAction("Frost", IE_Pressed, this, &GameMode::BuildFrost);

	//Spaw EnemySpawner
	mSpawner = EnemySpawner::Spawn(mGame);

	//HUD
	mHUD = HUD::Spawn(mGame);
}

void GameMode::SelectTile(){
	int x;
	int y;
	mGame.GetInput().GetMousePos(&x, &y);

	//Calculate the tile indexes
	x = (x-60)/50;
	y = (y-160)/50;

	
	if (y < mGrid.size() && x < mGrid[0].size()){
		//Reset the old selected tile
		if (mSelectedTile){
			if ((int)(mSelectedTile->GetTileStatus()) < 4){
				mSelectedTile->SetTileStatus(DEFAULT);
			}
			else {
				mSelectedTile->SetTileStatus(DEFAULT_ONPATH);
			}
			mSelectedTile = nullptr;
		}
		//Update the selected tile
		TilePtr tile = mGrid[y][x];
		if (tile->GetTileStatus() != GREEN && tile->GetTileStatus() != RED && 
			tile->GetTileStatus() != GREEN_ONPATH && tile->GetTileStatus() != RED_ONPATH){
			mSelectedTile = tile;
			if ((int)(tile->GetTileStatus()) < 4){
				tile->SetTileStatus(SELECTED);
			}
			else {
				tile->SetTileStatus(SELECTED_ONPATH);
			}
			
		}

	}
}

void GameMode::BuildCannon(){
	if (mSelectedTile){ 
		if (mSelectedTile->GetTower() == nullptr && mGame.GetNavWorld().SetBlockedNode(mSelectedTile->mPos) && mMoney >= mCannonTowerCost){
			auto cannon = CannonTower::SpawnAttached(*mSelectedTile);
			mSelectedTile->SetTower(cannon);

			mSelectedTile->SetTileStatus(DEFAULT);
			mSelectedTile = nullptr;

			mAudio->PlaySound(mBuildingSound);

			mMoney -= mCannonTowerCost;
		}
		else {

			if (mMoney < mCannonTowerCost){
				SetErrorMessage("Not enough money!");
			}
			else
				SetErrorMessage("Can't build a cannon tower here!");
			mAudio->PlaySound(mErrorSound);
		}
	}
}

void GameMode::BuildFrost(){
	if (mSelectedTile){
		if (mSelectedTile->GetTower() == nullptr && mGame.GetNavWorld().SetBlockedNode(mSelectedTile->mPos) && mMoney >= mFreezeTowerCost){
			auto frost = FrostTower::SpawnAttached(*mSelectedTile);
			mSelectedTile->SetTower(frost);

			mSelectedTile->SetTileStatus(DEFAULT);
			mSelectedTile = nullptr;

			mAudio->PlaySound(mBuildingSound);

			mMoney -= mFreezeTowerCost;
		}
		else{
			if (mMoney < mFreezeTowerCost){
				SetErrorMessage("Not enough money!");
			}
			else
				SetErrorMessage("Can't build a frost tower here!");
			mAudio->PlaySound(mErrorSound);
		}
	}
}

void GameMode::Damage(int damage){
	mHealth -= damage;

	if (mHealth <= 0){
		//Stop the Spawner
		mSpawner->SetIsAlive(false);
		SetIsAlive(false);
		SetErrorMessage("GameOver!");
	}
}