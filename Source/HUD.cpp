#include "HUD.h"
#include "Game.h"
#include "Font.h"
#include <string>
#include <sstream>

IMPL_ACTOR(HUD, Actor);

HUD::HUD(Game & game) : Actor(game){
}

void HUD::BeginPlay(){
	auto & assetCache = mGame.GetAssetCache();
	
	auto towerHealth = Actor::SpawnAttached(*this);
	mBaseHealthFont = FontComponent::Create(*towerHealth);
	towerHealth->SetPosition(Vector3(300.0f, 300.0f, 0.0f));

	auto playerMoney = Actor::SpawnAttached(*this);
	mPlayerMoneyFont = FontComponent::Create(*playerMoney);
	playerMoney->SetPosition(Vector3(-300.0f, 300.0f, 0.0f));

	auto errors = Actor::SpawnAttached(*this);
	mErrorFont = FontComponent::Create(*errors);
	errors->SetPosition(Vector3(0.0f, 0.0f, 0.0f));

	auto font = assetCache.Load<Font>("Fonts/Carlito-Regular.ttf");
	mBaseHealthFont->SetFont(font);
	mPlayerMoneyFont->SetFont(font);
	mErrorFont->SetFont(font);
}

void HUD::Tick(float deltaTime){
	std::string out = "Health: ";
	std::ostringstream stream;
	stream << mGame.GetGameMode()->GetHealth();
	out += stream.str();
	mBaseHealthFont->SetText(out, Color::Green, 30);
	mBaseHealthFont->SetAlignment(FontComponent::AlignRight);
	
	out = "Money: ";
	std::ostringstream mStream;
	mStream << mGame.GetGameMode()->GetMoney();
	out += mStream.str();
	mPlayerMoneyFont->SetText(out, Color::Blue, 30);
	mPlayerMoneyFont->SetAlignment(FontComponent::AlignLeft);

	out = mErrorMessage;
	mErrorFont->SetText(out, Color::Red, 30);
	mErrorFont->SetAlignment(FontComponent::AlignCenter);
}

void HUD::SetErrorMessage(std::string errorMessage) { 
	mErrorMessage = errorMessage;

	//Set the fire timer
	TimerHandle handle;
	mGame.GetTime().SetTimer(handle, this, &HUD::ClearError, 1.5f, true);
}

void HUD::ClearError(){
	mErrorMessage = "";
}

