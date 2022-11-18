#include "imp.h"

namespace imp_data {
	#include "walk1.h"
	#include "walk2.h"
	#include "walk3.h"
	#include "walk4.h"

	#include "aim.h"
	#include "shoot.h"

	//size is 45x60 pixels
}

imp::imp(float x, float y) {
	this->x = x;
	this->y = y;

	this->sprite = better_sprite::create(imp_data::walk1, 45, 60, .7, .7, x, y, 0);
}

imp* imp::create(float x, float y) {
	return new imp(x, y);
}

void imp::update(float dt, player* pdata) {

}

better_sprite* imp::get_sprite() {
	return this->sprite;
}

