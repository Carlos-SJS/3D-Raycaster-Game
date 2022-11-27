#include "../../BetterSprite.h"
#include "../../player.h"

class ebarrel : public colider, draw_obj, entity {
private:
	float x, y;

	better_sprite* sprite;
	better_sprite* exploding_sprite;

	//0 -> idle, 1 -> exploding, 2 -> exloded
	int state = 0;
	float animation_time = 0;
	int animation_step = 0;

	game_manager* manager;

public:
	ebarrel(float x, float y, game_manager* manager);
	static ebarrel* create(float x, float y, game_manager* manager);

	//Colider stuff
	void handle_collision(float damage);
	cocos2d::Vec3 get_pos();
	cocos2d::Vec2 get_rect();


	//Draw stuff
	better_sprite* get_sprite();


	bool update(float dt, player* pdata, std::vector<std::vector<int>>& map);

	void animator(float dt);

	bool is_solid();
	bool is_visible();
};