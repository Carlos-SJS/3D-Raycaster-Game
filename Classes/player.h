#pragma once

#include "cocos2d.h"
#include "BetterSprite.h"
#include <vector>

class colider {
public:
	virtual void handle_collision(float damage) = 0;
	virtual cocos2d::Vec3 get_pos() = 0;
	virtual cocos2d::Vec2 get_rect() = 0; 
	virtual bool is_solid() = 0;
};

class draw_obj {
public:
	virtual better_sprite* get_sprite() = 0;
	virtual bool is_visible() = 0;
};

struct target_entity {
	colider* obj;
	float dist;

	target_entity(colider* c, float d) : obj(c),dist(d){};
};

bool operator<(const target_entity& t1, const target_entity& t2);

struct player : public colider{
	float x;
	float y;
	float angle;
	float speed;

	int health = 100;
	int armor = 0;

	void handle_collision(float damage);
	cocos2d::Vec3 get_pos();
	cocos2d::Vec2 get_rect();
	bool is_solid();

};

class entity {
public:
	virtual bool update(float dt, player* player_data, std::vector<std::vector<int>>& map) = 0;
};

class game_manager {
public:
	virtual std::vector<colider*> get_objs(float x, float y, float z, float radius) = 0;
	virtual void handle_explosion(float x, float y, float z, float radius, int damage) = 0;
};