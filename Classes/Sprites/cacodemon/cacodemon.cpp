#include "cacodemon.h"
#include "cacodemon_projectile.h"

#include "AudioEngine.h"

#include "AngleUtil.h"

namespace cacodemon_data {
	#include "normal.h"

	#include "shoot1.h"
	#include "shoot2.h"
	#include "shoot3.h"

	#include "hurt.h"
	//size is 70x70 pixels

	#include "death1.h"
	#include "death2.h"
	#include "death3.h"
	#include "death4.h"
	#include "death5.h"
	#include "death6.h"

	//Size is 75.73

	int* death_s[] = {
		death1,
		death2,
		death3,
		death4,
		death5,
		death6
	};

	int* attack_s[] = {
		shoot1,
		shoot2,
		shoot3
	};
}

cacodemon::cacodemon(float x, float y, float z, game_manager* manager) {
	this->x = x;
	this->y = y;
	this->z = z;

	this->oz = z;

	this->sprite = better_sprite::create(cacodemon_data::normal, 70, 70, .6, .6, x, y, z);
	this->death_s = better_sprite::create(cacodemon_data::death1, 75, 73, .64, .625, x, y, z);

	this->manager = manager;
}

cacodemon* cacodemon::create(float x, float y, float z, game_manager* manager) {
	return new cacodemon(x, y, z, manager);
}

bool cacodemon::update(float dt, player* pdata, std::vector<std::vector<int>>& map) {
	if (!alive) return 0;

	if (cooldown > 0) cooldown -= dt;

	float dx = pdata->x - x;
	float dy = y - pdata->y;
	angle_to_player = angle_util::get_angle(dx, dy);

	player_sight = !manager->get_targets(x,y,angle_to_player,1).empty();

	if (!dying && !damaged) {
		//Move and shoot :)

		life_time += dt;

		if (cooldown <= 0 && !aiming && player_sight) aiming = 1;
		else if (player_sight && dx * dx + dy * dy < 18) {
			//try to get far from the player

			float cosa = -cos(angle_to_player);
			float sina = sin(angle_to_player);

			float dx = 1.3 * cosa * dt;
			float dy = 1.3 * sina * dt;

			if (map[(int)y][(int)(x + dx + .8 * cosa)] == 0 && manager->get_objs(x + dx, y, z, .3).size() == 1) x += dx;
			if (map[(int)(y + dy + .8 * sina)][(int)x] == 0 && manager->get_objs(x, y + dy, z, .3).size() == 1) y += dy;
		}
		else if (player_sight && dx * dx + dy * dy > 30) {
			float cosa = cos(angle_to_player);
			float sina = -sin(angle_to_player);

			float dx = 1.3 * cosa * dt;
			float dy = 1.3 * sina * dt;

			if (map[(int)y][(int)(x + dx + .8 * cosa)] == 0 && manager->get_objs(x + dx, y, z, .3).size() == 1) x += dx;
			if (map[(int)(y + dy + .8 * sina)][(int)x] == 0 && manager->get_objs(x, y + dy, z, .3).size() == 1) y += dy;
		}

		z = oz + sin(life_time)/10;

		sprite->set_position(x,y,z);

	}

	animator(dt);

	return 1;
}

void cacodemon::animator(float dt) {
	animator_time += dt;
	
	if (dying) {
		if (z > 0) {
			z = max(0, z - sz * dt);
			death_s->set_position(x, y, z);
		}

		if (animator_time > .1) {
			animator_frame++;

			animator_time = 0;

			if (animator_frame < 6) death_s->set_texture(cacodemon_data::death_s[animator_frame]);
			else alive = 0;
		}
	}
	else if (damaged) {
		if (animator_time > .3) {
			animator_time = 0;
			damaged = 0;

			normal = 1;

			sprite->set_texture(cacodemon_data::normal);
		}
	}
	else if (aiming) {
		if (animator_time > .08) {
			animator_frame++;
			animator_time = 0;

			if(animator_frame < 3) sprite->set_texture(cacodemon_data::attack_s[animator_frame]);
			else {
				sprite->set_texture(cacodemon_data::normal);
				
				animator_frame = 0;
				animator_time = 0;
				aiming = 0;
				cooldown = .9;

			}

			if (animator_frame == 2) {
				auto proj = cacodemon_projectile::create(x, y, z+.23, angle_to_player, manager);

				manager->add_to_draw((draw_obj*)proj);
				manager->add_to_update((entity*)proj);

				cocos2d::AudioEngine::play2d("audio/monster/cacodemon_attack.mp3");
			}
		}
	}
}

better_sprite* cacodemon::get_sprite() {
	if (dying) return this->death_s;
	return this->sprite;
}

void cacodemon::handle_collision(float damage) {
	hp -= damage;

	aiming = 0;

	if (hp > 0) {
		cocos2d::AudioEngine::play2d("audio/monster/cacodemon_hurt.mp3");

		sprite->set_texture(cacodemon_data::hurt);

		damaged = 1;
		animator_time = 0;
	}
	else {
		cocos2d::AudioEngine::play2d("audio/monster/cacodemon_death.mp3");

		animator_time = 0;
		dying = 1;
		sz = (z+.1) * 3.33;

		death_s->set_position(x, y, z);
	}
}

cocos2d::Vec3 cacodemon::get_pos() {
	return cocos2d::Vec3(this->x, this->y, this->z);
}

cocos2d::Vec2 cacodemon::get_rect() {
	return cocos2d::Vec2(sprite->get_sx(), sprite->get_sy());
}

bool cacodemon::is_solid() {
	return alive;
}

bool cacodemon::is_visible() {
	return 1;
}