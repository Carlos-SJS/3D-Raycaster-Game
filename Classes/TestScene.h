#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <cmath>
#include <string>
#include <sstream>
#include <algorithm>

#include "cocos2d.h"


#define PI 3.14159265    //Aprox. value of PI     (180°)
#define P2 1.570796325   //Aprox. value of PI/2   ( 90°)
#define P3 4.712388975   //Aprox. value of PI/3   (270°)

#define eps .0000001

#define UP_ARROW_KEY 0
#define DOWN_ARROW_KEY 1
#define LEFT_ARROW_KEY 2
#define RIGHT_ARROW_KEY 3
#define Q_KEY 4
#define E_KEY 5


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
							 {1,0,0,0,1,0,0,0,0,1},
							 {1,0,0,1,1,0,0,0,0,1},
							 {1,0,0,0,1,1,0,0,0,1},
							 {1,0,0,0,1,1,0,0,0,1},
							 {1,0,0,0,1,1,0,0,0,1},
							 {1,0,1,1,1,1,1,0,0,1},
							 {1,0,1,1,0,1,1,0,0,1},
							 {1,0,0,0,0,0,0,0,0,1},
							 {1,1,1,1,1,1,1,1,1,1}
							};

	bool key_states[6];
	float delta_mouse = 0.0;

	const int MAP_HEIGHT = 10;
	const int MAP_WIDTH = 10;

	const int WALL_SIZE = 64;

	int SCREEN_HEIGHT;
	int SCREEN_WIDTH;

	//In angle (radians) (100 deg)
	float fov = 1.39626;

	int ray_count;

	bool inside(float, float);

	void draw_rect(float, float, float, float, cocos2d::Color4F);

	std::string to_string(float);

	void handle_input(float);



public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void update(float) override;

	void draw_world();

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*);
	void onMouseMove(cocos2d::EventMouse*);

	CREATE_FUNC(TestScene);
};