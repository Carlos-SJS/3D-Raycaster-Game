#include "imp.h"

namespace imp_data {
	#include "walk1.h"
	#include "walk2.h"
	#include "walk3.h"
	#include "walk4.h"

	#include "aim.h"
	#include "shoot.h"

	#include "hurt.h"

	//size is 45x60 pixels
	
	#include "death1.h"
	#include "death2.h"
	#include "death3.h"
	#include "death4.h"
	#include "death5.h"
	
	//Size is 56x62

	int* death_s[] = {
		death1,
		death2,
		death3,
		death4,
		death5
	};

}

imp::imp(float x, float y) {
	this->x = x;
	this->y = y;

	this->sprite = better_sprite::create(imp_data::walk1, 45, 60, .7, .7, x, y, 0);
	this->death_s = better_sprite::create(imp_data::death1, 56, 62, .87, .73, x, y, 0);
}

imp* imp::create(float x, float y) {
	return new imp(x, y);
}

bool imp::update(float dt, player* padta, std::vector<std::vector<int>>& map) {
	if (!alive) return 0;

	animator(dt);

	return 1;
}

void imp::animator(float dt) {
	animation_time += dt;
	
	if (walking) {
		//Shit for walking animation
	}
	else if (damaged) {
		if (animation_time > .2) {
			if (hp > 0) {
				idle = 1;

				sprite->set_texture(imp_data::aim);
			}
			else {
				dying = 1;

				death_s->set_position(x, y);
			}

			damaged = 0;
			animation_time = 0;
		}
	}
	else if (dying) {
		if (animation_time > .1) {
			animation_frame++;
			if (animation_frame < 5) death_s->set_texture(imp_data::death_s[animation_frame]);
			else alive = 0;

			animation_time = 0;
		}
	}
}

better_sprite* imp::get_sprite() {
	if (dying) return this->death_s;
	return this->sprite;
}

void imp::handle_collision(float damage){
	hp -= damage;

	damaged = 1;
	idle = 0;

	animation_time = 0;

	this->sprite->set_texture(imp_data::hurt);
}

cocos2d::Vec3 imp::get_pos() {
	return cocos2d::Vec3(this->x, this->y, 0);
}

cocos2d::Vec2 imp::get_rect() {
	return cocos2d::Vec2(sprite->get_sx(), sprite->get_sy());
}

bool imp::is_solid() {
	return alive && !dying;
}

bool imp::is_visible() {
	return 1;
}
