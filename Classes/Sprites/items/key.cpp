#include "key.h"

namespace key_data {
#include "red_key.h"
};

key_item::key_item(float x, float y, int type, game_manager* manager) {
	this->sprite = better_sprite::create(key_data::red_key, 14, 16, .4, .428, x, y, 0);
	this->type = type;

	this->x = x;
	this->y = y;

	this->manager = manager;
}

key_item* key_item::create(float x, float y, int type, game_manager* manager) {
	return new key_item(x, y, type, manager);
}

better_sprite* key_item::get_sprite() {
	return this->sprite;
}

bool key_item::is_visible() {
	return exists;
}

bool key_item::update(float dt, player* player_data, std::vector<std::vector<int>>& map) {
	if (!exists) return 0;

	float dx = x - player_data->x;
	float dy = y - player_data->y;
	float dist = dx * dx + dy * dy;

	if (dist <= .16) {
		//0 red, 1 blue?
		manager->handle_key(type);
		exists = 0;
	}
}
