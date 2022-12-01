#pragma once

#include <cmath>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <queue>

#include "cocos2d.h"

#include "BetterSprite.h"
#include "AngleUtil.h"
#include "player.h"

#include "Sprites/entities.h"

#define PI 3.14159265    //Aprox. value of PI     (180°)
#define P2 1.570796325   //Aprox. value of PI/2   ( 90°)
#define P3 4.712388975   //Aprox. value of PI/3   (270°)

#define eps .0000001

#define min(a,b) (a<b?a:b)

#define UP_ARROW_KEY 0
#define DOWN_ARROW_KEY 1
#define LEFT_ARROW_KEY 2
#define RIGHT_ARROW_KEY 3
#define Q_KEY 4
#define E_KEY 5

class TestScene : public cocos2d::Scene, game_manager{
private:
	cocos2d::DrawNode* dNode;
	cocos2d::DrawNode* dNodeS;

	player player_data;

	// 0 -> void
	// 1 - texture_count -> texture index
	// -1 -> invisible barrier



	//Floor and ceiling have balues between 0 and amount of textures -1 only
	int ceiling_map[10][10] = {  {76,76,76,76,76,76,76,76,76,76},
								 {76,77,76,76,76,76,76,77,76,76},
								 {76,76,76,76,76,76,76,76,76,76},
								 {76,76,76,77,76,76,76,76,76,76},
								 {76,76,76,76,76,76,76,76,76,76},
								 {76,76,76,76,76,76,76,76,76,76},
								 {76,76,76,76,76,76,76,76,76,76},
								 {76,76,76,76,77,76,76,76,76,76},
								 {76,76,76,76,76,76,76,77,76,76},
								 {76,76,76,76,76,76,76,76,76,76},
							};

	int floor_map[10][10] = {{83,83,83,83,83,83,83,83,83,83},
							 {83,84,83,83,83,83,83,83,83,83},
							 {83,83,83,83,84,83,83,83,83,83},
							 {83,83,83,83,83,83,84,83,83,83},
							 {83,83,83,83,83,83,83,83,83,83},
							 {83,83,83,83,83,83,83,83,83,83},
							 {83,83,83,84,83,83,83,84,83,83},
							 {83,83,83,83,83,83,83,83,83,83},
							 {83,84,83,83,83,83,83,83,84,83},
							 {83,83,83,83,83,83,83,83,83,83},
							};

	std::vector<float> depth_map;

	//Sprites
	ebarrel* barrel1;
	zombie* zombie1;
	cacodemon* cdemon1;
	imp* imp1;

	cocos2d::Sprite* weapon_s;
	cocos2d::Sprite* face_s;
	cocos2d::Sprite* crosshair;
	cocos2d::Sprite* weapon_slot;

	cocos2d::Sprite* ammo_text[3];
	cocos2d::Sprite* hp_text[4];
	cocos2d::Sprite* armor_text[4];

	int hp_tv = 0;
	int ammo_tv = 0;
	int armor_tv = 5;


	std::vector<draw_obj*> draw_list;
	std::vector<entity*> update_list;
	std::vector<colider*> solid_obj_list;

	imp_projectile* impp1;

	bool key_states[6];
	float delta_mouse = 0.0;

	const int MAP_HEIGHT = 10;
	const int MAP_WIDTH = 10;

	const int WALL_SIZE = 64;

	//In angle (radians) (100 deg)
	float fov = 1.39626;

	int ray_count;

	bool inside(float, float);

	void draw_rect(float, float, float, float, cocos2d::Color4F);

	std::string to_string(float);

	void handle_input(float);

	void schedule_sprite(better_sprite* sprite);
	void draw_sprite(float dist, float a, better_sprite* sprite);
	void draw_sprites();
	void handle_sprites();

	std::priority_queue<buffered_sprite > sprite_queue;

	float face_cooldown=0;

	void handle_player_shot();

	//Anamtion shit
	void player_animator(float dt);
	
	float weapon_anim_timer = 0;
	bool weapon_cooldown = 0;
	bool pending_damage = 0;
	float weapon_swapping = 0;
	int weapon_s_state = 0; //o: lowering, 1:rising
	float weapon_speed = 400;

	// 0 -> fist?, 1 -> shity gun
	int weapon_id = 1;
	int weapon_frame = 2;

	int crosshair_mode = 0;

	std::vector<std::vector<std::string>> weapon_textures{ 
		{"weapons/fist/punch1.png", "weapons/fist/punch2.png", "weapons/fist/punch3.png", "weapons/fist/punch2.png", "weapons/fist/punch1.png", "weapons/fist/normal.png"},
		{"weapons/pistol/shoot1.png", "weapons/pistol/shoot2.png", "weapons/pistol/pistol1.png"}, 
		{"weapons/shotgun/shot1.png", "weapons/shotgun/shot2.png", "weapons/shotgun/shot3.png", "weapons/shotgun/shot4.png", "weapons/shotgun/shot5.png", "weapons/shotgun/shot4.png", "weapons/shotgun/shot3.png", "weapons/shotgun/sgun1.png"}
	};
	std::vector<std::vector<float>> weapon_f_time{
		{.09, .09, .15, .08, .08, 0},
		{.15, .18, 0},
		{.1,.1,.15,.15,.15, .12, 0}
	};
	std::vector<int> w_ammo{-1, 45, 25};

	std::vector<int> weapon_damage {20, 30, 105};

	std::vector<bool> weapon_unlocked {1, 1, 0};

	
	std::priority_queue<target_entity> targets;

	void update_hp_text();
	void update_ammo_text();
	void update_armor_text();


	cocos2d::Vec2 point_buffer[4000];
	cocos2d::Color4F color_buffer[4000];

	void swap_weapon(int weapon);

public:
	std::vector<std::vector<int>> world_map 
					   { { 1, 1, 7,21,13,12,13, 7, 1, 1},
						 { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						 { 1, 0, 0, 1, 1, 0, 0, 0, 0, 1},
						 { 3, 0, 0, 0, 1, 1, 0, 0, 0, 1},
						 { 1, 0, 0, 0, 1, 1, 0, 0, 0, 1},
						 { 1, 0, 0, 0, 1, 1, 0, 0, 0, 1},
						 { 1, 0, 1, 1, 1, 1, 1, 0, 0, 1},
						 { 1, 0, 1, 1, 0, 1, 1, 0, 0, 1},
						 { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						 { 1, 1, 2, 1, 4, 1, 1, 1, 4, 1}
	};


	static cocos2d::Scene* createScene();

	virtual bool init();

	void update(float) override;

	void draw_world();

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*);
	void onMouseMove(cocos2d::EventMouse*);
	void onMouseDown(cocos2d::EventMouse*);

	//Stuff for shots, damage and collisions
	std::priority_queue<target_entity> get_targets(float x, float y, float a, bool player_only = 0);
	std::vector<colider*> get_objs(float x, float y, float z, float radius);
	void handle_explosion(float x, float y, float z, float radius, int damage);

	void handle_ammo(int type, int amount);
	void handle_healing(int type, int amount);
	void handle_weapon(int type);

	CREATE_FUNC(TestScene);
};