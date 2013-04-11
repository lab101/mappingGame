#pragma once
#include "uiSprite.h"
#include "AppConstants.h"

class Window : public uiSprite{
	float lastHit;
	float respawnTime;
	float openTime;
public:
	Window();
	void setHit();
	void update();
	void reset();

	int points;
    bool isClosed;

	PrizeType currentWindowType;

};