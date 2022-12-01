#include "terminal.h"
#include "AudioEngine.h"

terminal::terminal(int x, int y, std::vector<std::vector<int>>* mp, bool* flag) {
	this->x = (float)x + .5;
	this->y = (float)y + .5;

	ax = x;
	ay = y;

	this->activate_flag = flag;

	map = mp;
}

terminal* terminal::create(int x, int y, std::vector<std::vector<int>>* mp, bool* target) {
	return new terminal(x, y, mp, target);
}

void terminal::check(float px, float py, bool rk, bool bk) {
	float dx = x - px;
	float dy = y - py;
	
	if (dx * dx + dy * dy <= dist * dist) {
		is_active = 0;
		*activate_flag = 1;

		(*map)[ay][ax] = 36;
		cocos2d::AudioEngine::play2d("audio/misc/target.mp3");
	}
}

bool terminal::active() {
	return is_active;
}