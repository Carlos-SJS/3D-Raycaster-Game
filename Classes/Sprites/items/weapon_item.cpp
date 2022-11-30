#include "weapon_item.h"

namespace weapon_data {
#include "witem_1.h"
#include "witem_2.h"
#include "witem_3.h"

	int* sprites[] = { witem_1, witem_2, witem_3};
};

weapon_item::weapon_item(float x, float y, int type, game_manager* manager) {
	this->sprite = better_sprite::create(weapon_data::sprites[type-1], 63, 16, .7, .178, x, y, 0);
	this->type = type;

	this->x = x;
	this->y = y;

	this->manager = manager;
}

weapon_item* weapon_item::create(float x, float y, int type, game_manager* manager) {
	return new weapon_item(x, y, type, manager);
}

better_sprite* weapon_item::get_sprite() {
	return this->sprite;
}

bool weapon_item::is_visible() {
	return exists;
}

bool weapon_item::update(float dt, player* player_data, std::vector<std::vector<int>>& map) {
	if (!exists) return 0;

	float dx = x - player_data->x;
	float dy = y - player_data->y;
	float dist = dx * dx + dy * dy;

	if (dist <= .16) {
		manager->handle_weapon(type);
		exists = 0;
	}
}
