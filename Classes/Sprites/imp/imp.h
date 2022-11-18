#pragma once

#include "../../BetterSprite.h"
#include "../../player.h" 

class imp {
private:
	float x, y;
	better_sprite* sprite;
public:
	imp(float x, float y);
	static imp* create(float x, float y);

	void update(float dt, player* pdata);

	better_sprite* get_sprite();
};