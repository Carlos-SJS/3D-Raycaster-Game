#include "cacodemon.h"

namespace cacodemon_data {
	#include "normal.h"

	#include "shoot1.h"
	#include "shoot2.h"
	#include "shoot3.h"

	#include "hurt.h"
	//size is 70x70 pixels

	#include "death1.h"
	#include "death2.h"
	#include "death3.h"
	#include "death4.h"
	#include "death5.h"
	#include "death6.h"

	//Size is 75.73

	int* death_s[] = {
		death1,
		death2,
		death3,
		death4,
		death5,
		death6
	};
}

cacodemon::cacodemon(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;

	this->sprite = better_sprite::create(cacodemon_data::normal, 70, 70, .6, .6, x, y, z);
	this->death_s = better_sprite::create(cacodemon_data::death1, 75, 73, .64, .625, x, y, z);
}

cacodemon* cacodemon::create(float x, float y, float z) {
	return new cacodemon(x, y, z);
}

bool cacodemon::update(float dt, player* padta, std::vector<std::vector<int>>& map) {
	if (!alive) return 0;

	animator(dt);

	return 1;
}

void cacodemon::animator(float dt) {
	animator_time += dt;
	
	if (dying) {
		if (z > 0) {
			z = max(0, z - sz * dt);
			death_s->set_position(x, y, z);
		}

		if (animator_time > .1) {
			animator_frame++;

			animator_time = 0;

			if (animator_frame < 6) death_s->set_texture(cacodemon_data::death_s[animator_frame]);
			else alive = 0;
		}
	}
	else if (damaged) {
		if (animator_time > .3) {
			animator_time = 0;
			damaged = 0;

			normal = 1;

			sprite->set_texture(cacodemon_data::normal);
		}
	}
}

better_sprite* cacodemon::get_sprite() {
	if (dying) return this->death_s;
	return this->sprite;
}

void cacodemon::handle_collision(float damage) {
	hp -= damage;

	if (hp > 0) {
		sprite->set_texture(cacodemon_data::hurt);

		damaged = 1;
		animator_time = 0;
	}
	else {
		animator_time = 0;
		dying = 1;
		sz = (z+.1) * 3.33;

		death_s->set_position(x, y, z);
	}
}

cocos2d::Vec3 cacodemon::get_pos() {
	return cocos2d::Vec3(this->x, this->y, this->z);
}

cocos2d::Vec2 cacodemon::get_rect() {
	return cocos2d::Vec2(sprite->get_sx(), sprite->get_sy());
}

bool cacodemon::is_solid() {
	return alive;
}

bool cacodemon::is_visible() {
	return 1;
}