#pragma once

#include "../../BetterSprite.h"
#include "../../player.h" 

class imp : public entity, colider, draw_obj {
private:
	float x, y;
	better_sprite* sprite;
public:
	imp(float x, float y);
	static imp* create(float x, float y);

	bool update(float dt, player* padta, std::vector<std::vector<int>>& map);

	//Colider stuff
	cocos2d::Vec4 get_pos();
	void handle_collision(float damage);

	better_sprite* get_sprite();

	bool is_alive();
};