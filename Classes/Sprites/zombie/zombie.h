#pragma once

#include <vector>

#include "../../BetterSprite.h"
#include "../../player.h"

#include "cocos2d.h"

#include <random>
#include <time.h>

class zombie : public entity, colider, draw_obj{
private:
	better_sprite* sprite;
	better_sprite* death_s;

	game_manager* manager;

	float x, y;

	float animator_timer;
	
	bool walking = 1;
	int wsc = 0;
	int wanim_d = 1;

	bool aim = 0;
	bool shooting = 0;
	bool damaged = 0;
	bool dying = 0;

	int animation_frame=0;

	bool alive = 1;

	int hp = 100;

	float stun_time = 0;

	float  angle_to_player = 0;
	float lplayerx=-1, lplayery=-1;

	bool player_s = 0;
	float player_sight_counter = 0;

	float aim_counter = 0;

	float weapon_cooldown = 0;

	//Zombie damage to enemies
	int dmg = 20;


public:
	zombie(float x, float y, game_manager* manager);
	static zombie* create(float x, float y, game_manager* manager);

	bool update(float ft, player* pdata, std::vector<std::vector<int>> &map);
	void animator(); //Controls entity animations

	//Collision related stuff
	cocos2d::Vec3 get_pos();
	cocos2d::Vec2 get_rect();

	void handle_collision(float damage);

	better_sprite* get_sprite();

	bool is_visible();
	bool is_solid();
};
