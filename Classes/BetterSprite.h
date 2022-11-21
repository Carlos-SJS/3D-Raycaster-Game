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
	void set_texture(int* t);
};

struct buffered_sprite {
	float dist;
	float angle;

	better_sprite* sprite;

	buffered_sprite(float d, float a, better_sprite* s);

	void set(float d, float a, better_sprite* s);

};

bool operator<(const buffered_sprite& s1, const buffered_sprite& s2);