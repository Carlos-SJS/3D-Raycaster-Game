#include "../../player.h"
#include "../../BetterSprite.h"

#include <random>
#include <time.h>

class cacodemon_projectile : public entity, draw_obj {
private:
	float x, y, z;
	float dx, dy;
	float angle;

	game_manager* manager;

	better_sprite* sprite;
	better_sprite* e_sprite;

	float animator_time = 0;
	int animator_frame = 0;

	bool alive = 1;

	int state = 0;
	
	float life_time = 0;

public:

	cacodemon_projectile(float x, float y, float z, float angle, game_manager* manager);
	static cacodemon_projectile* create(float x, float y, float z, float angle, game_manager* manager);

	bool update(float dt, player* pdata, std::vector<std::vector<int>>& mp);

	void animator(float dt);

	better_sprite* get_sprite();
	bool is_visible();

	void handle_explotion(float dt);
};