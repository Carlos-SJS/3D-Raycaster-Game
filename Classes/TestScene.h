#pragma once
#include <cmath>
#include <string>
#include <sstream>
#include <algorithm>

#include "cocos2d.h"

#define PI 3.14159265
#define P2 1.570796325
#define P3 4.712388975

#define eps .0000001

#define UP_ARROW_KEY 0
#define DOWN_ARROW_KEY 1
#define LEFT_ARROW_KEY 2
#define RIGHT_ARROW_KEY 3


struct player {
	float x;
	float y;
	float angle;
	float speed;
};

class TestScene : public cocos2d::Scene{
private:
	cocos2d::DrawNode* dNode;

	player player_data;


	int world_map[10][10] = {{1,1,1,1,1,1,1,1,1,1},
							 {1,0,0,1,0,0,0,0,0,1},
							 {1,0,0,1,0,0,0,0,0,1},
							 {1,0,0,0,0,0,0,0,0,1},
							 {1,0,0,0,0,0,0,0,0,1},
							 {1,0,0,0,0,0,0,0,0,1},
							 {1,0,0,0,0,0,0,0,0,1},
							 {1,0,0,0,0,0,0,0,0,1},
							 {1,0,0,0,0,0,0,0,0,1},
							 {1,1,1,1,1,1,1,1,1,1}
							};

	bool key_states[4];

	const int MAP_HEIGHT = 10;
	const int MAP_WIDTH = 10;

	const int WALL_SIZE = 64;

	//In angle (radians) (100 deg)
	float fov = 1.39626;

	int ray_count = 100;

	bool inside(float, float);

	void draw_rect(float, float, float, float, cocos2d::Color4F);

	std::string to_string(float);

public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void update(float) override;

	void draw_world();

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*);

	CREATE_FUNC(TestScene);
};