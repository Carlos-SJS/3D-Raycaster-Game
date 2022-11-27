#pragma once

#include <vector>
#include <cmath>

#include "../../BetterSprite.h"
#include "../../player.h"

class imp_projectile : public entity, draw_obj {
private:
	float x, y, z;
	float angle;

	float dx, dy;

	//0 - Normal, 1 -> Exploding, 2 -> exploded
	int state = 0;

	float animator_time = 0;
	int texture_index = 0;

	better_sprite* sprite;
	better_sprite* e_sprite;
	
	void animator(float dt);

	void handle_explotion(float dt);

	game_manager* manager;

public:
	imp_projectile(float x, float y, float z, float angle, game_manager* manager);
	static imp_projectile* create(float x, float y, float z, float angle, game_manager* manager);

	bool update(float dt, player* padta, std::vector<std::vector<int>>& map);

	better_sprite* get_sprite();

	bool is_visible();
};