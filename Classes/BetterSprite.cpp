#include "BetterSprite.h"

better_sprite::better_sprite(int* texture, int t_width, int t_height, float scaleX, float scaleY, float x, float y, float z) {
	this->texture = texture;
	this->t_width = t_width;
	this->t_height = t_height;

	this->scaleX = scaleX;
	this->scaleY = scaleY;

	this->x = x;
	this->y = y;
	this->z = z;
}

float better_sprite::get_z() {
	return this->z;
}

cocos2d::Vec2 better_sprite::get_position() {
	return cocos2d::Vec2(x, y);
}

void better_sprite::set_position(float x, float y) {
	this->x = x;
	this->y = y;
}

void better_sprite::set_texture(int* t) {
	this->texture = t;
}

better_sprite* better_sprite::create(int* t, int t_width, int t_height, float scaleX, float scaleY, float x, float y, float z) {
	cocos2d::log("Size of the texture array is %d", (int)sizeof(t));

	better_sprite* sp = new better_sprite(t, t_width, t_height, scaleX, scaleY, x, y, z);
	
	return sp;
}

float better_sprite::get_sx() {
	return this->scaleX;
}

float better_sprite::get_sy() {
	return this->scaleY;
}

int* better_sprite::get_texture() {
	return this->texture;
}

cocos2d::Vec2 better_sprite::get_tsize() {
	return cocos2d::Vec2(t_width, t_height);
}