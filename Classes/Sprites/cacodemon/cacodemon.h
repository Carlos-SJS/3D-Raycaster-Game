#pragma once

#include "../../BetterSprite.h"
#include "../../player.h"

class cacodemon : public entity, colider, draw_obj {
private:
	float x, y, z;

	better_sprite* sprite;

public:
	cacodemon(float x, float y, float z);
	static cacodemon* create(float x, float y, float z);

	bool update(float dt, player* padta, std::vector<std::vector<int>>& map);

	//Colider stuff
	void handle_collision(float damge);
	cocos2d::Vec4 get_pos();

	better_sprite* get_sprite();

	bool is_alive();
};