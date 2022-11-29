#include "ammo_item.h"

namespace ammo_data {
#include "ammo_box.h"
#include "bullets.h"
#include "shells.h"

	int* sprites[] = {ammo_box, bullets, shells};
};

ammo_item::ammo_item(float x, float y, int type, int amount, game_manager* manager) {
	this->sprite = better_sprite::create(ammo_data::sprites[type], 28, 16, .4, .228, x, y, 0);
	this->type = type;
	this->ammount = amount;

	this->x = x;
	this->y = y;

	this->manager = manager;
}

ammo_item* ammo_item::create(float x, float y, int type, int amount, game_manager* manager) {
	return new ammo_item(x, y, type, amount, manager);
}

better_sprite* ammo_item::get_sprite() {
	return this->sprite;
}

bool	ammo_item::is_visible() {
	return exists;
}

bool ammo_item::update(float dt, player* player_data, std::vector<std::vector<int>>& map) {
	if (!exists) return 0;

	float dx = x - player_data->x;
	float dy = y - player_data->y;
	float dist = dx*dx + dy*dy;

	if (dist <= .16) {
		manager->handle_ammo(type == 0 ? -1:type , ammount);
		exists = 0;
	}
}
