#pragma once

#include "cocos2d.h"

class better_sprite {
private:
	int* texture;
	int t_width;
	int t_height;

	float scaleX;
	float scaleY;

	float x;
	float y;
	float z;

public:
	better_sprite(int*, int, int, float, float, float, float, float);

	static better_sprite* create(int* texture, int t_width, int t_height, float scaleX, float scaleY, float x, float y, float z);

	cocos2d::Vec2 get_position();
	cocos2d::Vec2 get_tsize();

	float get_z();

	float get_sx();
	float get_sy();

	int* get_texture();

	void set_position(float, float);
};