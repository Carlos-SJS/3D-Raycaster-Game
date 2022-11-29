#include "healing_item.h"

namespace healing_data {
#include "bandages.h"
#include "medkit.h"
#include "shield1.h"
#include "shield2.h"

	int* sprites[] = { bandages, medkit, shield1, shield2 };

	int ammount[] = { 20, 50, 30, 60 };
};

healing_item::healing_item(float x, float y, int type, game_manager* manager) {
	this->sprite = better_sprite::create(healing_data::sprites[type], 31, 19, .4, .228, x, y, 0);
	this->type = type;

	this->x = x;
	this->y = y;

	this->manager = manager;
}

healing_item* healing_item::create(float x, float y, int type, game_manager* manager) {
	return new healing_item(x, y, type, manager);
}

better_sprite* healing_item::get_sprite() {
	return this->sprite;
}

bool healing_item::is_visible() {
	return exists;
}

bool healing_item::update(float dt, player* player_data, std::vector<std::vector<int>>& map) {
	if (!exists) return 0;

	float dx = x - player_data->x;
	float dy = y - player_data->y;
	float dist = dx * dx + dy * dy;

	if (dist <= .16) {
		manager->handle_healing(type/2, healing_data::ammount[type]);
		exists = 0;
	}
}
