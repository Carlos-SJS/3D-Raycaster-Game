#include "imp_projectile.h"

namespace imp_proj_data {
	#include "projectile1.h"
	#include "projectile2.h"

	#include "explode1.h"
	#include "explode2.h"
	#include "explode3.h"

	//size is 15x15
	int* projectile[] = { projectile1, projectile2 };
	
	//size is 50x44
	int* explotion[] = { explode1, explode2, explode3 };
}

imp_projectile::imp_projectile(float x, float y, float z, float angle) {
	this->x = x;
	this->y = y;
	this->z = z;

	this->angle = angle;
	
	this->dx = 2.0*cos(angle);
	this->dy = 2.0*sin(angle);

	this->sprite = better_sprite::create(imp_proj_data::projectile1, 15, 15, .3, .3, x, y, z);
	this->e_sprite = better_sprite::create(imp_proj_data::explode1, 50, 44, .6, .528, 0, 0, z);
}

imp_projectile* imp_projectile::create(float x, float y, float z, float angle) {
	return new imp_projectile(x, y, z, angle);
}

//Returns 0 if projectile exploded
bool imp_projectile::update(float dt, std::vector<std::vector<int>>& map) {
	if (this->state == 0) {
		if (map[y - dt*dy][x + dt*dx] == 0) {
			this->x += dt*this->dx;
			this->y -= dt*this->dy;

			sprite->set_position(x,y);
		}
		else {
			this->handle_explotion(dt);
		}
	}
	this->animator(dt);

	return this->state != 2;
}

void imp_projectile::animator(float dt) {
	animator_time += dt;

	if (this->state == 0) {
		if (animator_time >= .2) {
			animator_time = 0;
			texture_index = (texture_index + 1) & 1;
			this->sprite->set_texture(imp_proj_data::projectile[texture_index]);
		}
	}
	else if (this->state == 1) {
		if (animator_time >= .16) {
			animator_time = 0;
			texture_index++;
			if (texture_index == 3) { this->state = 2; return; }
			this->e_sprite->set_texture(imp_proj_data::explotion[texture_index]);
		}
	}
}

void imp_projectile::handle_explotion(float dt) {
	this->animator_time = -dt;
	this->state = 1;
	this->e_sprite->set_position(this->x, this->y);
}


better_sprite* imp_projectile::get_sprite() {
	if (this->state == 0) return this->sprite;
	else return this->e_sprite;
}