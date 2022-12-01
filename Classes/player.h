#pragma once

#include "cocos2d.h"
#include "BetterSprite.h"
#include <vector>
#include <queue>

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
	virtual std::priority_queue<target_entity> get_targets(float x, float y, float a, bool player_only = 0) = 0;

	//type 0-> hp, 1 -> shield
	virtual void handle_healing(int type, int ammount) = 0;
	virtual void handle_weapon(int type) = 0;
	//type -1 -> all, 1 -> pistol, 2->shotgun, 3->macjinegun?
	virtual void handle_ammo(int type, int amount) = 0;
};