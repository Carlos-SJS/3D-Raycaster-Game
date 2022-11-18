#include "zombie.h"

namespace zombie_data {
	#include "walk1.h"
	#include "walk2.h"
	#include "walk3.h"
	#include "walk4.h"

	#include "aim.h"
	#include "shoot.h"

	#include "hurt.h"

	//size is 35x55 pixels

	int* walk_s[] = {
		walk1,
		walk2,
		walk3,
		walk4
	};
}

zombie::zombie(float x, float y) {
	this->x = x;
	this->y = y;

	this->sprite = better_sprite::create(zombie_data::walk1, 35, 55, 0.38, .6, x, y, 0);

	this->animator_timer = 0;
}

zombie* zombie::create(float x, float y) {
	return new zombie(x, y);
}

void zombie::update(float dt, player* pdata, std::vector<std::vector<int>> &map) {
	float dx = x - pdata->x ;
	float dy = y - pdata->y;

	//Move zombie to follow 
	if (abs(dx) + abs(dy) > 0.5) {
		//cocos2d::log("this is a test, map[0][0] = %d, map[9][9] = %d", map[0][0], map[9][9]);
		if (map[(int)y][(int)(x - 1.4 * dt * (dx / (abs(dx) + abs(dy))))] == 0) x -= 1.0 * dt * (dx / (abs(dx) + abs(dy)));
		if (map[(int)(y - 1.4 * dt * (dy / (abs(dx) + abs(dy))))][(int)x] == 0) y -= 1.0 * dt * (dy / (abs(dx) + abs(dy)));

		sprite->set_position(x, y);
	}

	animator_timer += dt;
	this->animator();
}

void zombie::animator() {
	if (walking) {
		if (animator_timer >= .3) {
			wsc++; wsc = wsc %= 2;

			animator_timer = 0;

			sprite->set_texture(zombie_data::walk_s[1+wsc]);
		}
	}
	else if (aim) {
		//Handle aiming anmimation
	}
	else if (shooting) {
		//Handling shooting animation
	}
	else if (damaged) {
		//handle damage animation
	}
}

better_sprite* zombie::get_sprite() {
	return this->sprite;
}