#include "cacodemon_projectile.h"

#include "AudioEngine.h"

namespace cproj_data {
	#include "normalp1.h"
	#include "normalp2.h"
	//Size is 16x16

	#include "explode1.h"
	#include "explode2.h"
	//Size is 53x48

	int* normal_s[] = {normal1, normal2};

	int* exploding_s[] = {explode1, explode2};

}

cacodemon_projectile::cacodemon_projectile(float x, float y, float z, float angle, game_manager* manager) {
	this->x = x;
	this->y = y;
	this->z = z;

	this->angle = angle;

	this->dx = 8 * cos(angle);
	this->dy = 8 * sin(angle);

	this->manager = manager;

	this->sprite = better_sprite::create(cproj_data::normal1, 16, 16, .3, .3, x, y, z);
	this->e_sprite = better_sprite::create(cproj_data::explode1, 53, 48, .6, .6, x, y, z);
}

cacodemon_projectile* cacodemon_projectile::create(float x, float y, float z, float angle, game_manager* manager) {
	return new cacodemon_projectile(x, y, z, angle, manager);
}

bool cacodemon_projectile::update(float dt, player* pdata, std::vector<std::vector<int>>& map) {
	if (!alive) return 0;

	life_time += dt;

	if (this->state == 0) {
		if (map[y - dt * dy][x + dt * dx] == 0) {
			this->x += dt * this->dx;
			this->y -= dt * this->dy;

			sprite->set_position(x, y);

			if (life_time > .1) if (!manager->get_objs(x, y, z, .2).empty()) this->handle_explotion(dt);
		}
		else {
			this->handle_explotion(dt);
		}
	}

	animator(dt);

	return 1;
}

void cacodemon_projectile::animator(float dt) {
	animator_time += dt;
	
	if (state == 0) {
		if (animator_time > .1) {
			animator_frame++; animator_frame &= 1;
			animator_time = 0;

			sprite->set_texture(cproj_data::normal_s[animator_frame]);
		}
	}
	else if (state == 1) {
		if (animator_time >= .16) {
			animator_time = 0;
			animator_frame++;
			if (animator_frame == 2) { this->alive = 0; return; }
			this->e_sprite->set_texture(cproj_data::exploding_s[animator_frame]);
		}
	}
}

better_sprite* cacodemon_projectile::get_sprite() {
	if (state == 1) return this->e_sprite;
	return this->sprite;
}

bool cacodemon_projectile::is_visible() {
	return alive;
}

void cacodemon_projectile::handle_explotion(float dt) {
	this->animator_time = -dt;
	this->state = 1;
	this->e_sprite->set_position(this->x, this->y);

	cocos2d::AudioEngine::play2d("audio/monster/cproj_explode.mp3");
	manager->handle_explosion(x, y, z, .25, 50);
}
