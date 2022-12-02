#include "zombie.h"
#include "AudioEngine.h"
#include "AngleUtil.h"



namespace zombie_data {
	#include "walk1.h"
	#include "walk2.h"
	#include "walk3.h"
	#include "walk4.h"

	#include "aim.h"
	#include "shoot.h"

	#include "hurt.h"

	#include "dying1.h"
	#include "dying2.h"
	#include "dying3.h"
	#include "dying4.h"
	#include "dying5.h"

	//size is 35x55 pixels

	int* walk_s[] = {
		walk1,
		walk2,
		walk3,
		walk4
	};

	int* death_s[] = {
		dying1,
		dying2,
		dying3,
		dying4,
		dying5
	};
}

zombie::zombie(float x, float y, game_manager* manager) {
	this->x = x;
	this->y = y;

	this->sprite = better_sprite::create(zombie_data::walk1, 35, 55, 0.38, .6, x, y, 0);
	this->death_s = better_sprite::create(zombie_data::dying1, 50, 60, .54, .65, x, y, 0);

	this->animator_timer = 0;

	this->manager = manager;

	srand(time(NULL));
}

zombie* zombie::create(float x, float y, game_manager* manager) {
	return new zombie(x, y, manager);
}

bool zombie::update(float dt, player* pdata, std::vector<std::vector<int>> &map){
	if (!alive) return 0;

	/*
	Idle untill it sees the player for the first time
	Follows the player when is not in sight

	Can move pseudo randomly when player is in sight and within a distance

	when player is in sigt can try to aim anx`d shot the player if possible

	*/

	float dx = pdata->x - x;
	float dy = y - pdata->y;

	angle_to_player = angle_util::get_angle(dx, dy);

	auto target = manager->get_targets(x, y, angle_to_player, 1);

	if (weapon_cooldown > 0) weapon_cooldown -= dt;

	if (dying || damaged) goto ignore_stuff;

	if (!shooting) {
		if (!target.empty()) {  //Player is in view
			lplayery = pdata->y;
			lplayerx = pdata->x;

			player_sight_counter += dt;

			if (aim) {
				aim_counter += dt;
				if (aim_counter > .5) {
					target = manager->get_targets(x, y, angle_to_player);
					if (!target.empty() && target.top().obj == this) target.pop();
					if(!target.empty()) target.top().obj->handle_collision(dmg);

					cocos2d::AudioEngine::play2d("audio/weapon/pistol.mp3");

					sprite->set_texture(zombie_data::shoot);

					aim = 0;
					shooting = 1;
					walking = 0;
					aim_counter = 0;
					animator_timer = 0;
				}

				goto ignore_stuff;

			}
			if ((!aim && !shooting) && (target.top().dist > 10 || (player_sight_counter < 1 && target.top().dist > (float)(rand()&3000)/1000.0) )) {
				float dx = x - lplayerx;
				float dy = y - lplayery;

				walking = 1;

				if (map[(int)y][(int)(x - 1.4 * dt * (dx / (abs(dx) + abs(dy))))] == 0 && manager->get_objs(x- 1.0 * dt * (dx / (abs(dx) + abs(dy))), y, 0, .5).size() == 1) x -= 1.0 * dt * (dx / (abs(dx) + abs(dy)));
				if (map[(int)(y - 1.4 * dt * (dy / (abs(dx) + abs(dy))))][(int)x] == 0 && manager->get_objs(x, y- 1.0 * dt * (dy / (abs(dx) + abs(dy))), 0, .5).size() == 1) y -= 1.0 * dt * (dy / (abs(dx) + abs(dy)));

				sprite->set_position(x, y);
			}
			else if (weapon_cooldown <= 0 && !aim) {
				aim_counter = 0, aim = 1, walking = 0;

				sprite->set_texture(zombie_data::aim);
			}
			else player_sight_counter = (float)(rand()%700)/1000.0;
		}
		else {
			if (lplayerx == -1 || lplayery == -1) goto ignore_stuff;

			walking = 1;
			aim = 0;

			player_sight_counter = 0;

			float dx = x - lplayerx;
			float dy = y - lplayery;

			//Move zombie to follow 
			if (dx * dx + dy * dy > 0.01) {
				//cocos2d::log("this is a test, map[0][0] = %d, map[9][9] = %d", map[0][0], map[9][9]);
				if (map[(int)y][(int)(x - 1.4 * dt * (dx / (abs(dx) + abs(dy))))] == 0) x -= 1.0 * dt * (dx / (abs(dx) + abs(dy)));
				if (map[(int)(y - 1.4 * dt * (dy / (abs(dx) + abs(dy))))][(int)x] == 0) y -= 1.0 * dt * (dy / (abs(dx) + abs(dy)));

				sprite->set_position(x, y);
			}
			else walking = 0;
		}
	}

	ignore_stuff:

	/*if (walking) {
		float dx = x - pdata->x;
		float dy = y - pdata->y;

		//Move zombie to follow 
		if (dx * dx + dy * dy > 0.49) {
			//cocos2d::log("this is a test, map[0][0] = %d, map[9][9] = %d", map[0][0], map[9][9]);
			if (map[(int)y][(int)(x - 1.4 * dt * (dx / (abs(dx) + abs(dy))))] == 0) x -= 1.0 * dt * (dx / (abs(dx) + abs(dy)));
			if (map[(int)(y - 1.4 * dt * (dy / (abs(dx) + abs(dy))))][(int)x] == 0) y -= 1.0 * dt * (dy / (abs(dx) + abs(dy)));

			sprite->set_position(x, y);
		}
	}*/

	animator_timer += dt;
	this->animator();

	return 1;
}

void zombie::animator() {
	if (walking) {
		if (animator_timer >= .3) {
			wsc++; wsc %= 2;

			animator_timer = 0;

			sprite->set_texture(zombie_data::walk_s[1+wsc]);
		}
	}
	else if (shooting) {
		//Handling shooting animation
		if (animator_timer > .2) {
			shooting = 0;
			if(rand() % 2) player_sight_counter = 0;
			weapon_cooldown = 1 + (float)(rand()%60)/10.0;

			animator_timer = 0;

			sprite->set_texture(zombie_data::walk_s[0]);
		}

	}
	else if (damaged) {
		if (animator_timer > .2) {

			if (hp > 0) {
				damaged = 0;
				walking = 1;
				animator_timer = 0;

				sprite->set_texture(zombie_data::walk_s[0]);
			}
			else {
				dying = 1;
				damaged = 0;
				animator_timer = 0;
				animation_frame = 0;

				death_s->set_position(x, y);
			}
		}
	}
	else if (dying) {
		if (animator_timer > .1) {
			animation_frame++;
			animator_timer = 0;

			if (animation_frame < 5) death_s->set_texture(zombie_data::death_s[animation_frame]);
			else alive = 0;
		}
	}
}

better_sprite* zombie::get_sprite() {
	if (dying) return this->death_s;
	return this->sprite;
}

cocos2d::Vec3 zombie::get_pos() {
	return cocos2d::Vec3(this->x, this->y, 0);
}

cocos2d::Vec2 zombie::get_rect() {
	return cocos2d::Vec2(sprite->get_sx(), sprite->get_sy());
}

void zombie::handle_collision(float damage) {
	hp -= damage;

	if (hp > 0) cocos2d::AudioEngine::play2d("audio/monster/zombie_hurt.mp3");
	else {
		cocos2d::AudioEngine::play2d("audio/monster/zombie_death.mp3");
		manager->add_kill();
	}

	sprite->set_texture(zombie_data::hurt);

	damaged = 1;

	walking = 0;
	aim = 0;
	shooting = 0;
	animator_timer = 0;
	aim_counter = 0;
}

bool zombie::is_solid() {
	return !dying;
}

bool zombie::is_visible() {
	return true;
}