#include "door.h"
#include "AudioEngine.h"

door::door(int x, int y, std::vector<std::vector<int>> *map, int r) {
	this->mp = mp;
	ax = x;
	ay = y;

	this->x = (float) x + .5;
	this->y = (float) y + .5;

	this->key = r;

	this->mp = map;
}

door* door::create(int x, int y, std::vector<std::vector<int>>* mp, int req) {
	return new door(x, y, mp, req);
}

void door::check(float px, float py, bool rk, bool bk) {
	float dx = x - px;
	float dy = y - py;

	if (dx * dx + dy * dy <= dist * dist && (key == 0 || (key == 1 && rk) || (key == 2) && bk)) {//Open the door D:
		open = 1;
		(*mp)[ay][ax] = 0;

		cocos2d::AudioEngine::play2d("audio/misc/door_open.mp3");
	}
}

bool door::active() {
	return !open;
}