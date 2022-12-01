#pragma once

#include "../../BetterSprite.h"
#include "../../player.h"

#define max(a,b) (a>b?a:b)

class cacodemon : public entity, colider, draw_obj {
private:
	float x, y, z;

	better_sprite* sprite;
	better_sprite* death_s;

	bool normal = 1;
	bool damaged = 0;
	bool dying = 0;
	bool alive = 1;

	int hp = 200;

	float animator_time = 0;
	int animator_frame = 0;

	float cooldown = 1;

	float sz = 0;

	bool aiming = 0;

	float angle_to_player = 0;

	bool player_sight = 0;

	float life_time = 0;
	float oz;

	game_manager* manager;

public:
	cacodemon(float x, float y, float z, game_manager* manager);
	static cacodemon* create(float x, float y, float z, game_manager* manager);

	bool update(float dt, player* padta, std::vector<std::vector<int>>& map);

	void animator(float dt);

	//Colider stuff
	void handle_collision(float damge);
	cocos2d::Vec3 get_pos();
	cocos2d::Vec2 get_rect();

	better_sprite* get_sprite();

	bool is_solid();
	bool is_visible();
};