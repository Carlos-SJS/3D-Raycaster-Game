#include "imp.h"
#include "imp_projectile.h"
#include "AngleUtil.h"

#include "AudioEngine.h"


namespace imp_data {
	#include "walk1.h"
	#include "walk2.h"
	#include "walk3.h"
	#include "walk4.h"

	#include "walk1_l.h"
	#include "walk2_l.h"
	#include "walk1_r.h"
	#include "walk2_r.h"
	#include "walk1_b.h"
	#include "walk2_b.h"

	#include "aim.h"
	#include "shoot.h"

	#include "hurt.h"

	//size is 45x60 pixels
	
	#include "death1.h"
	#include "death2.h"
	#include "death3.h"
	#include "death4.h"
	#include "death5.h"
	
	//Size is 56x62

	int* death_s[] = {
		death1,
		death2,
		death3,
		death4,
		death5
	};

	int* walk_s[] = {
		walk1,
		walk2,
		walk1_l,
		walk2_l,
		walk1_r,
		walk2_r,
		walk1_b,
		walk2_b
	};

}

imp::imp(float x, float y, game_manager* manager) {
	this->x = x;
	this->y = y;

	this->sprite = better_sprite::create(imp_data::walk1, 45, 60, .7, .7, x, y, 0);
	this->death_s = better_sprite::create(imp_data::death1, 56, 62, .87, .73, x, y, 0);

	this->manager = manager;

	srand(time(NULL));
}

imp* imp::create(float x, float y, game_manager* manager) {
	return new imp(x, y, manager);
}

bool imp::update(float dt, player* pdata, std::vector<std::vector<int>>& map) {
	if (!alive) return 0;

	if (active && cooldown > 0) cooldown -= dt;

	float dx = pdata->x - x;
	float dy = y - pdata->y;
	angle_to_player = angle_util::get_angle(dx, dy);
	
	if (aiming || shooting || damaged || dying) goto skip_stuff;

	if (!manager->get_targets(x, y, angle_to_player, 1).empty()) {
		if (!active) active = 1;

		if (cooldown <= 0) {
			//Shoot a ball :)
			aiming = 1;
			walking = 0;
			animation_time = 0;
			moving = ~(rand() % 3/2);
		}
		else if(moving){
			//try to move to avoid shooting other monsters
			goto move_rnd;
		}
	}
	else {
		move_rnd:
		
		if (!active) goto skip_stuff;

		float cosa = cos(dir);
		float sina = -sin(dir);

		float dx = cosa*.8;
		float dy = sina*.8;

		walking = 1;
		if (map[(int)y][(int)(x - dx * dt + .5 * cosa)] == 0 && map[(int)(y - dy * dt + .5 * sina)][(int)x] == 0 && manager->get_objs(x, y, 0, .4).size() == 1) {
			x += dx*dt;
			y += dy*dt;

			sprite->set_position(x, y);
		}
		else {
			walking = 0;



			dir = (float)(rand()% 62830)/10000.0;
		}
	}

	skip_stuff:

	animator(dt);

	return 1;
}

void imp::animator(float dt) {
	animation_time += dt;
	
	if (walking) {
		//Shit for walking animation
		if (animation_time >= .3) {
			animation_frame++; animation_frame %= 2;

			int offset = 0;
			float a = dir-angle_to_player;
			a = angle_util::fix(a);

			if ((a < PI / 3 && a > 0) || (a < 0) && a > 5 * PI / 3) offset = 0;
			else if ((a > 2 * PI / 3 && a < 4 * PI / 3)) offset = 6;
			else if (a < PI) offset = 4;
			else offset = 2;

			animation_time = 0;

			sprite->set_texture(imp_data::walk_s[offset + animation_frame]);
		}
	}
	else if (damaged) {
		if (animation_time > .2) {
			if (hp > 0) {
				idle = 1;

				sprite->set_texture(imp_data::aim);
			}
			else {
				dying = 1;

				death_s->set_position(x, y);
			}

			damaged = 0;
			animation_time = 0;
		}
	}
	else if (dying) {
		if (animation_time > .1) {
			animation_frame++;
			if (animation_frame < 5) death_s->set_texture(imp_data::death_s[animation_frame]);
			else alive = 0;

			animation_time = 0;
		}
	}
	else if (aiming) {
		if (animation_time > .2) {
			shooting = 1;

			auto proj = imp_projectile::create(x, y, .4, angle_to_player, manager);
			cocos2d::AudioEngine::play2d("audio/monster/imp_attack.mp3");

			manager->add_to_draw((draw_obj*) proj);
			manager->add_to_update((entity*) proj);

			sprite->set_texture(imp_data::shoot);
			aiming = 0;
			shooting = 1;
			animation_time = 0;
		}
	}
	else if (shooting) {
		if (animation_time > 1.6) {
			shooting = 0;
			cooldown = 3;

			sprite->set_texture(imp_data::walk1);
		}
	}
}

better_sprite* imp::get_sprite() {
	if (dying) return this->death_s;
	return this->sprite;
}

void imp::handle_collision(float damage){
	hp -= damage;

	damaged = 1;
	idle = 0;
	aiming = 0;
	walking = 0;

	animation_time = 0;

	this->sprite->set_texture(imp_data::hurt);

	if (hp > 0) cocos2d::AudioEngine::play2d("audio/monster/imp_hurt.mp3");
	else cocos2d::AudioEngine::play2d("audio/monster/imp_death.mp3");

}

cocos2d::Vec3 imp::get_pos() {
	return cocos2d::Vec3(this->x, this->y, 0);
}

cocos2d::Vec2 imp::get_rect() {
	return cocos2d::Vec2(sprite->get_sx(), sprite->get_sy());
}

bool imp::is_solid() {
	return alive && !dying;
}

bool imp::is_visible() {
	return 1;
}
