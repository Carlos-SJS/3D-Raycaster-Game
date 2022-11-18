#pragma once

#include "../../BetterSprite.h"
#include "../../player.h"

class cacodemon{
private:
	float x, y, z;

	better_sprite* sprite;

public:
	cacodemon(float x, float y, float z);
	static cacodemon* create(float x, float y, float z);

	void update(float dt, player* pdata);

	better_sprite* get_sprite();
};