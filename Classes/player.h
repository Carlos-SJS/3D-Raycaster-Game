#pragma once

#include "cocos2d.h"
#include "BetterSprite.h"
#include <vector>

struct player {
	float x;
	float y;
	float angle;
	float speed;
};

class colider {
public:
	virtual void handle_collision(float damage) = 0;
	virtual cocos2d::Vec4 get_pos() = 0;
	//virtual bool alive() = 0;
};

class entity {
public:
	virtual bool update(float dt, player* player_data, std::vector<std::vector<int>>& map) = 0;
};

class draw_obj {
public:
	virtual better_sprite* get_sprite() = 0;
	virtual bool is_alive() = 0;
};