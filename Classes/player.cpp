#include "player.h"
#include "AudioEngine.h"

#define min(a,b) (a<b?a:b)

bool operator<(const target_entity& t1, const target_entity& t2) {
	return -t1.dist < -t2.dist;
}


void player::handle_collision(float damage) {
	int protect = min(armor, damage/2);
	health -= damage - protect;
	armor -= protect;

	cocos2d::AudioEngine::play2d("audio/player/hurt.mp3");
}

cocos2d::Vec3 player::get_pos() {
	return cocos2d::Vec3(x, y, 0);
}

cocos2d::Vec2 player::get_rect() {
	return cocos2d::Vec2(0.38, .6);
}

bool player::is_solid() {
	return 1;
}