#pragma once

#include "../../BetterSprite.h"
#include "../../player.h" 

#include <random>
#include <time.h>

class imp : public entity, colider, draw_obj {
private:
	float x, y;
	
	better_sprite* sprite;
	better_sprite* death_s;

	bool idle = 1;
	bool walking = 0;
	bool damaged = 0;
	bool dying = 0;

	bool aiming = 0;
	bool shooting = 0;

	bool alive = 1;

	int hp = 100;

	float animation_time = 0;

	float cooldown = 3;
	float angle_to_player = 0;

	int animation_frame = 0;

	float dir = 0;

	bool active = 0;


	bool moving = 0;

	game_manager* manager;

public:
	imp(float x, float y, game_manager* manager);
	static imp* create(float x, float y, game_manager* manager);

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