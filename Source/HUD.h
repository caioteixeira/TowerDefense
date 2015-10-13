#pragma once
#include "Actor.h"
#include "FontComponent.h"

class HUD : public Actor {
	DECL_ACTOR(HUD, Actor);
public:
	HUD(Game & game);
	void Tick(float deltaTime) override;
	void SetErrorMessage(std::string errorMessage);
	void BeginPlay() override;
private:
	void ClearError();
	FontComponentPtr mBaseHealthFont;
	FontComponentPtr mPlayerMoneyFont;
	FontComponentPtr mErrorFont;
	std::string mErrorMessage = "";
};

DECL_PTR(HUD);