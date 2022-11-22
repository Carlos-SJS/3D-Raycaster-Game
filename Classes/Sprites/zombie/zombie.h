#pragma once

#include <vector>

#include "../../BetterSprite.h"
#include "../../player.h"

#include "cocos2d.h"

class zombie : public entity, colider, draw_obj{
private:
	better_sprite* sprite;

	float x, y;

	float animator_timer;
	
	bool walking = 1;
	int wsc = 0;
	int wanim_d = 1;

	bool aim = 0;
	bool shooting = 0;
	bool damaged = 0;

	bool alive = 1;

public:
	zombie(float x, float y);
	static zombie* create(float x, float y);

	bool update(float ft, player* pdata, std::vector<std::vector<int>> &map);
	void animator(); //Controls entity animations

	//Collision related stuff
	cocos2d::Vec4 get_pos();
	void handle_collision(float damage);

	better_sprite* get_sprite();

	bool is_alive();
};
