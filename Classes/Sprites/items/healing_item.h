#include "../../player.h"
#include "../../BetterSprite.h"

class healing_item : public  draw_obj, entity {
private:
	better_sprite* sprite;

	game_manager* manager;

	bool exists = 1;

	float x, y;

	//0 -> all, 1 -> bullets, 2 -> shells
	int type;

public:
	healing_item(float x, float y, int type, game_manager* manager);
	static healing_item* create(float x, float y, int type, game_manager* manager);

	better_sprite* get_sprite();
	bool is_visible();

	bool update(float dt, player* player_data, std::vector<std::vector<int>>& map);
};