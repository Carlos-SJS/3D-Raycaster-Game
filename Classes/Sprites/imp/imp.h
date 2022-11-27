#pragma once

#include "../../BetterSprite.h"
#include "../../player.h" 

class imp : public entity, colider, draw_obj {
private:
	float x, y;
	
	better_sprite* sprite;
	better_sprite* death_s;

	bool idle = 1;
	bool walking = 0;
	bool damaged = 0;
	bool dying = 0;

	bool alive = 1;

	int hp = 100;

	float animation_time = 0;
	int animation_frame = 0;

public:
	imp(float x, float y);
	static imp* create(float x, float y);

	bool update(float dt, player* padta, std::vector<std::vector<int>>& map);

	void animator(float dt);

	//Colider stuff
	cocos2d::Vec3 get_pos();
	cocos2d::Vec2 get_rect();

	void handle_collision(float damage);

	better_sprite* get_sprite();

	bool is_solid();
	bool is_visible();
};