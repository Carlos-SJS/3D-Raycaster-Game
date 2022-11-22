#include "ebarrel.h"

namespace ebarrel_data {
	#include "ebarrel_texture.h"
	//Size is 36x36


	#include "eb_explosion1.h"
	#include "eb_explosion2.h"
	#include "eb_explosion3.h"
	//Size is 60x60

	int* explosion[] = {explosion1, explosion2, explosion3};
}

ebarrel::ebarrel(float x, float y) {
	this->x = x;
	this->y = y;

	this->sprite = better_sprite::create(ebarrel_data::ebarrel, 36, 36, .6, .6, x, y, 0);
	this->exploding_sprite = better_sprite::create(ebarrel_data::explosion[0], 60, 60, .84, .84, x, y, 0);
}

ebarrel* ebarrel::create(float x, float y) {
	return new ebarrel(x, y);
}

cocos2d::Vec4 ebarrel::get_pos() {
	return cocos2d::Vec4(this->x, this->y, 0, .6);
}

void ebarrel::handle_collision(float damage) {
	state = 1;
	animation_time = 0;
	animation_step = 0;
}

better_sprite* ebarrel::get_sprite() {
	if (state == 0) return this->sprite;
	else return exploding_sprite;
}

bool ebarrel::update(float dt, player* pdata, std::vector<std::vector<int>>& map) {
	if (state == 1) animator(dt);

	return state != 2;
}

void ebarrel::animator(float dt) {
	animation_time += dt;
	if (animation_time > .17) {
		animation_step++;
		if (animation_step == 4) { state = 2; return; }
		
		exploding_sprite->set_texture(ebarrel_data::explosion[animation_step]);
	}
}

bool ebarrel::is_alive() {
	return state != 2;
}