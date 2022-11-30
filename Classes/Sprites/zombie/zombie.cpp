#include "zombie.h"
#include "AudioEngine.h"


namespace zombie_data {
	#include "walk1.h"
	#include "walk2.h"
	#include "walk3.h"
	#include "walk4.h"

	#include "aim.h"
	#include "shoot.h"

	#include "hurt.h"

	#include "dying1.h"
	#include "dying2.h"
	#include "dying3.h"
	#include "dying4.h"
	#include "dying5.h"

	//size is 35x55 pixels

	int* walk_s[] = {
		walk1,
		walk2,
		walk3,
		walk4
	};

	int* death_s[] = {
		dying1,
		dying2,
		dying3,
		dying4,
		dying5
	};
}

zombie::zombie(float x, float y) {
	this->x = x;
	this->y = y;

	this->sprite = better_sprite::create(zombie_data::walk1, 35, 55, 0.38, .6, x, y, 0);
	this->death_s = better_sprite::create(zombie_data::dying1, 50, 60, .54, .65, x, y, 0);

	this->animator_timer = 0;
}

zombie* zombie::create(float x, float y) {
	return new zombie(x, y);
}

bool zombie::update(float dt, player* pdata, std::vector<std::vector<int>> &map){
	if (!alive) return 0;

	
	if (walking) {
		float dx = x - pdata->x;
		float dy = y - pdata->y;

		//Move zombie to follow 
		if (dx * dx + dy * dy > 0.49) {
			//cocos2d::log("this is a test, map[0][0] = %d, map[9][9] = %d", map[0][0], map[9][9]);
			if (map[(int)y][(int)(x - 1.4 * dt * (dx / (abs(dx) + abs(dy))))] == 0) x -= 1.0 * dt * (dx / (abs(dx) + abs(dy)));
			if (map[(int)(y - 1.4 * dt * (dy / (abs(dx) + abs(dy))))][(int)x] == 0) y -= 1.0 * dt * (dy / (abs(dx) + abs(dy)));

			sprite->set_position(x, y);
		}
	}

	animator_timer += dt;
	this->animator();

	return 1;
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
		if (animator_timer > .2) {

			if (hp > 0) {
				damaged = 0;
				walking = 1;
				animator_timer = 0;

				sprite->set_texture(zombie_data::walk_s[0]);
			}
			else {
				dying = 1;
				damaged = 0;
				animator_timer = 0;
				animation_frame = 0;

				death_s->set_position(x, y);
			}
		}
	}
	else if (dying) {
		if (animator_timer > .1) {
			animation_frame++;
			animator_timer = 0;

			if (animation_frame < 5) death_s->set_texture(zombie_data::death_s[animation_frame]);
			else alive = 0;
		}
	}
}

better_sprite* zombie::get_sprite() {
	if (dying) return this->death_s;
	return this->sprite;
}

cocos2d::Vec3 zombie::get_pos() {
	return cocos2d::Vec3(this->x, this->y, 0);
}

cocos2d::Vec2 zombie::get_rect() {
	return cocos2d::Vec2(sprite->get_sx(), sprite->get_sy());
}

void zombie::handle_collision(float damage) {
	hp -= damage;

	if (hp > 0) cocos2d::AudioEngine::play2d("audio/monster/zombie_hurt.mp3");
	else cocos2d::AudioEngine::play2d("audio/monster/zombie_death.mp3");

	sprite->set_texture(zombie_data::hurt);

	damaged = 1;
	walking = 0;
	animator_timer = 0;
}

bool zombie::is_solid() {
	return !dying;
}

bool zombie::is_visible() {
	return true;
}