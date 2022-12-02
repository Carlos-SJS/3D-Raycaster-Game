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

class level_2 : public cocos2d::Scene, game_manager{
private:
	cocos2d::DrawNode* dNode;
	cocos2d::DrawNode* dNodeS;

	player player_data;

	// 0 -> void
	// 1 - texture_count -> texture index
	// -1 -> invisible barrier



	//Floor and ceiling have balues between 0 and amount of textures -1 only
	int ceiling_map[23][20] = {
		{ 1, 1, 1, 1, 1, 8, 1,20, 1, 1, 1, 1, 8, 1, 1, 1, 1, 1, 1, 1},
		{ 1, 1,64,64,64,64,64,64,64, 1,78,78,78,78,78,78,78, 1,78, 1},
		{ 1, 1,64,64,64,64,64,64,64, 1,78,78, 8, 1, 1,78,78, 5,78, 1},
		{ 8,64, 1, 1,64,64,64,64, 1, 1,78,78,78,78,78,78,78,78,78, 1},
		{ 1,64, 1,64,64,64,64, 1, 1, 1, 8, 1,16,76,16,78,87, 1,78,18},
		{ 2,64, 1,64,64,64,64, 1, 1, 1, 1,15,76,76,76,12,12, 1,78,22},
		{ 7,64,64,64,64, 1, 1, 1, 1,14,76,76,76,77,76,76,76,12,78, 1},
		{ 1, 1, 1,64, 1, 1, 1, 1, 6,76,77,76,76,76,76,76,76,76,13, 1},
		{ 1,64,64,64,64,64,64, 1,12, 6,76,76,76,76,76,76,76,76,14, 1},
		{10,64,64,64,64,64,64,16,76,76,76,76,76,76,77,76,76,76,77,16},
		{ 1, 8,64,64,64,64,64,76,76,76,77,76,76,91,76,76,76,76,76,14},
		{ 1, 1, 1,64, 1, 1, 1,17,76,76,76,76,76,76,76,76,76,76,76,17},
		{ 1, 1, 1,64, 1, 1, 1, 1,13,76,77,76,76,76,76,76,76,76, 6, 1},
		{ 1, 1, 8,64, 1, 1, 1, 1,12,76,76,76,76,76,77,76,76,76,13, 1},
		{ 1, 1, 1,64, 7, 1, 1, 1, 1,15,76,76,76,76,76,76,76,15,39,38},
		{ 1, 2, 1,64, 8, 1, 1, 1,38, 1, 6,14,76,76,76,12,12,38,78,38},
		{ 1,64,64,64,64,64, 8,38,78,38, 1, 1,16,76,16, 1,38,78,78,38},
		{ 1,64,64,64,64,64, 3,38,78,78,39,38,38,87,38,39,78,78,78,38},
		{ 1,64,64,21,64,64, 1,39,78,78,78,78,38,78,78,78,78,78,78,39},
		{ 1,64,18, 1,37,64,64,78,78,78,78,78,39,38,38,78,78,78,78,38},
		{ 1,64,64,21,64,64, 1,38,78,78,78,78,78,78,78,78,78,38,38, 1},
		{ 1,64,64,64,64,64, 8,38,78,78,78,78,78,78,78,78,78,39, 1, 1},
		{ 1, 1, 3,33, 1, 7, 1,38,39,38,38,39,38,38,38,38,38,38, 1, 1}
	};

	int floor_map[23][20] = {
		{ 1, 1, 1, 1, 1, 8, 1,20, 1, 1, 1, 1, 8, 1, 1, 1, 1, 1, 1, 1},
		{ 1, 1,83,83,83,83,84,83,83, 1,83,83,84,83,83,83,83, 1,83, 1},
		{ 1, 1,84,83,83,83,83,83,83, 1,83,83, 8, 1, 1,83,83, 5,84, 1},
		{ 8,83, 1, 1,83,83,83,83, 1, 1,83,84,83,83,83,83,83,83,83, 1},
		{ 1,83, 1,83,83,83,83, 1, 1, 1, 8, 1,16,71,16,83,83, 1,83,18},
		{ 2,83, 1,83,83,83,84, 1,83,83, 1,15,70,70,70,12,12, 1,83,22},
		{ 7,83,83,83,83, 1, 1,83,83,14,70,70,70,70,70,70,70,12,84, 1},
		{ 1, 1, 1,83, 1, 1, 1,83, 6,70,70,70,72,70,70,70,70,70,13, 1},
		{ 1,83,83,83, 1,83, 1,83,12,70,70,70,70,89,70,72,70,70,14, 1},
		{10,83,83,83, 1,83, 1,16,71,72,70,70,89,89,89,70,70,70,70,16},
		{ 1, 8,83,83,83,83,83,70,70,70,70,89,89,89,89,89,70,72,70,14},
		{ 1, 1, 1,83, 1, 1, 1,17,70,70,70,70,89,89,89,70,70,70,70,17},
		{83,83, 1,83, 1, 1, 1, 1,13,71,70,70,70,89,70,72,70,70, 6, 1},
		{83,83, 8,83, 1, 1, 1, 1,12,70,70,70,72,70,70,70,70,71,13, 1},
		{83,83, 1,84, 7, 1, 1, 1, 1,15,70,70,70,70,70,70,70,15,39,38},
		{ 1, 2, 1,87, 8, 1, 1, 1,38, 1, 6,14,70,70,70,12,12,38,64,38},
		{ 1,87,87,87,88,87, 8,38,64,38, 1, 1,16,72,16, 0,38,64,64,38},
		{ 1,87,87,87,87,87, 3,38,64,63,39,38,38,64,38,39,64,64,64,38},
		{ 1,87,88,21,87,87, 1,39,64,64,64,64,38,64,63,64,64,64,64,39},
		{ 1,87,18, 1,37,88,87,64,64,64,64,64,39,38,38,64,64,64,63,38},
		{ 1,87,87,21,87,87, 1,38,64,64,64,63,64,64,64,64,64,38,38, 1},
		{ 1,87,87,88,87,87, 8,38,64,64,64,64,64,64,64,63,64,39, 1, 1},
		{ 1, 1, 3,33, 1, 7, 1,38,39,38,38,39,38,38,38,38,38,38, 1, 1}
	};

	std::vector<float> depth_map;

	//Sprites

	cocos2d::Sprite* weapon_s;
	cocos2d::Sprite* face_s;
	cocos2d::Sprite* crosshair;
	cocos2d::Sprite* weapon_slot;
	cocos2d::Sprite* death_effect;
	cocos2d::Sprite* pause_effect;

	cocos2d::Sprite* ammo_text[3];
	cocos2d::Sprite* hp_text[4];
	cocos2d::Sprite* armor_text[4];
	
	cocos2d::Sprite* kills_text[4];
	cocos2d::Sprite* items_text[4];

	int total_kills = 33;
	int total_items = 19;

	int hp_tv = 0;
	int ammo_tv = 0;
	int armor_tv = 5;


	std::vector<draw_obj*> draw_list;
	std::vector<entity*> update_list;
	std::vector<colider*> solid_obj_list;
	std::vector<interactable*> interactable_list;

	imp_projectile* impp1;

	bool key_states[6];
	float delta_mouse = 0.0;

	const int MAP_HEIGHT = 23;
	const int MAP_WIDTH = 20;

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

	bool paused = 0;

	void handle_pause();
	void handle_unpause();

	cocos2d::Menu* menu;

	void show_stat_menu();
	void level_2::show_defeat_menu();

	int player_kills = 0;
	int items_collected = 0;

public:


	std::vector<std::vector<int>> world_map {
		{ 0, 1, 1, 1, 1, 8, 1,20, 1, 1, 1, 1, 8, 1, 1, 1, 1, 1, 1, 1},
		{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
		{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 8, 1, 1, 0, 0, 5, 0, 1},
		{ 8, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{ 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 8, 1,16,96,16, 0, 0, 1, 0,18},
		{ 2, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1,15, 0, 0, 0,12,12, 1, 0,22},
		{ 7, 0, 0, 0, 0, 1, 1, 0, 0,14, 0, 0, 0, 0, 0, 0, 0,12, 0, 1},
		{ 1, 1, 1, 0, 1, 1, 1, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0,13, 1},
		{ 1, 0, 0, 0, 1, 0, 1, 0,12, 0, 0, 0, 0, 0, 0, 0, 0, 0,14, 0},
		{10, 0, 0, 0, 1, 0, 1,16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,16},
		{ 1, 8, 0, 0, 0, 0, 0,96, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,14},
		{ 1, 1, 1, 0, 1, 1, 1,17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,17},
		{ 0, 0, 1, 0, 1, 0, 0, 0,13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0},
		{ 0, 0, 8, 0, 1, 0, 0, 0,12, 0, 0, 0, 0, 0, 0, 0, 0, 0,13, 0},
		{ 0, 0, 1, 0, 7, 0, 0, 0, 0,15, 0, 0, 0, 0, 0, 0, 0,15,39,38},
		{ 1, 2, 1,97, 8, 1, 1, 0,38, 0, 6,14, 0, 0, 0,12,12,38, 0,38},
		{ 1, 0, 0, 0, 0, 0, 8,38, 0,38, 0, 0,16,96,16, 0,38, 0, 0,38},
		{ 1, 0, 0, 0, 0, 0, 3,38, 0, 0,39,38,38, 0,38,39, 0, 0, 0,38},
		{ 1, 0, 0,21, 0, 0, 1,39, 0, 0, 0, 0,38, 0, 0, 0, 0, 0, 0,39},
		{ 1, 0,18, 1,37, 0,97, 0, 0, 0, 0, 0,39,38,38, 0, 0, 0, 0,38},
		{ 1, 0, 0,21, 0, 0, 1,38, 0, 0, 0, 0, 0, 0, 0, 0, 0,38,38, 0},
		{ 1, 0, 0, 0, 0, 0, 8,38, 0, 0, 0, 0, 0, 0, 0, 0, 0,39, 0, 0},
		{ 1, 1, 3,33, 1, 7, 1,38,39,38,38,39,38,38,38,38,38,38, 0, 0}
	};

	bool target_reached = 0;

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
	void handle_key(int type);

	void add_to_solid(colider* obj);
	void add_to_draw(draw_obj* obj);
	void add_to_update(entity* obj);

	void resume_callback(Ref* psender);
	void menu_callback(Ref* psdener);

	void add_kill();

	CREATE_FUNC(level_2);
};

void handle_key(int type);