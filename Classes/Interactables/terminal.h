#include "../player.h"
#include <vector>

class terminal : public interactable {
private:
	float x, y;
	int ax, ay;
	float dist = 1;

	bool* activate_flag;
	bool is_active = 1;

	std::vector<std::vector<int>>* map;

public:
	terminal(int x, int y, std::vector<std::vector<int>>* mp, bool* activated_flag);
	static terminal* create(int x, int y, std::vector<std::vector<int>>* mp, bool* flag);

	void check(float x, float y, bool rk, bool bk);
	bool active();
};