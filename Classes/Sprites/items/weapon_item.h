#include "../../player.h"
#include "../../BetterSprite.h"

class weapon_item : public  draw_obj, entity {
private:
	better_sprite* sprite;

	game_manager* manager;

	bool exists = 1;

	float x, y;

	//1 -> pistol, 2 -> shotgun, 3 -> machinegun?
	int type;

public:
	weapon_item(float x, float y, int type, game_manager* manager);
	static weapon_item* create(float x, float y, int type, game_manager* manager);

	better_sprite* get_sprite();
	bool is_visible();

	bool update(float dt, player* player_data, std::vector<std::vector<int>>& map);
};