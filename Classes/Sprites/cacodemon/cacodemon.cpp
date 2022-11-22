#include "cacodemon.h"

namespace cacodemon_data {
	#include "normal.h"

	#include "shoot1.h"
	#include "shoot2.h"
	#include "shoot3.h"

	//size is 70x70 pixels
}

cacodemon::cacodemon(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;

	this->sprite = better_sprite::create(cacodemon_data::normal, 70, 70, .6, .6, x, y, z);
}

cacodemon* cacodemon::create(float x, float y, float z) {
	return new cacodemon(x, y, z);
}

bool cacodemon::update(float dt, player* padta, std::vector<std::vector<int>>& map) {

	return 1;
}

better_sprite* cacodemon::get_sprite() {
	return this->sprite;
}

void cacodemon::handle_collision(float damge) {

}

cocos2d::Vec4 cacodemon::get_pos() {
	return cocos2d::Vec4(this->x, this->y, this->z, .6);
}

bool cacodemon::is_alive() {
	return 1;
}