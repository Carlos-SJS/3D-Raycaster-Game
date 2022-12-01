#include "../player.h"
#include <vector>

class door : public interactable {
private:
	float dist = 1;
	float x, y;

	std::vector<std::vector<int>>* mp;

	int key = 0;
	
	int ax, ay;

	bool open = 0;

public:
	door(int ax, int ay, std::vector<std::vector<int>>* mp, int r);
	static door* create(int ax, int ay, std::vector<std::vector<int>>* mp, int req  = 0);

	void check(float px, float py, bool rk, bool bk);
	bool active();
};