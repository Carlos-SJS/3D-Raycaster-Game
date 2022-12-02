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

class level_1 : public cocos2d::Scene, game_manager{
private:
	cocos2d::DrawNode* dNode;
	cocos2d::DrawNode* dNodeS;

	player player_data;

	// 0 -> void
	// 1 - texture_count -> texture index
	// -1 -> invisible barrier



	//Floor and ceiling have balues between 0 and amount of textures -1 only
	int ceiling_map[20][20] = {
		{ 0,45,44,44,44,44,44,44, 1,29,24,29,24,23,29,24, 1, 1, 1, 1 },
		{ 0,63,64,64,64,64,64,44, 1,27,78,78,78,78,78,29,23,29, 1, 1 },
		{ 0,64,64,63,64,44,64,44, 1,29,25,29,24,78,78,78,78,29, 1, 1 },
		{ 0,64,64,64,64,45,64,44, 1, 1, 1,29,29,78,78,78,78,25, 1, 1 },
		{ 0,64,64,64,63,44,64,44, 1, 1,29,79,78,78,25,78,78,23, 1, 1 },
		{ 0,63,64,64,64,64,63,44, 1,24,78,78,78,29,29,78,79,23,29,29 },
		{ 0,44,63,44,44,44,44,44, 1,24,78,78,78,23,78,78,78,29,79,29 },
		{ 0,47,64,46,64, 1,29,29,29,29,78,78,78,78,78,78,29,29,78,29 },
		{ 0,50,64,50,49,29,31,78,78,78,78,29,29,78,78,78,29,78,78,23 },
		{ 0,49,64,64,64,78,78,79,78,78,78,29,28,78,78,78,29,78,78,24 },
		{ 0,50,64,49,50,29,29,29,29,78,78,78,29,29,79,29,29,78,78,23 },
		{ 0,48,64,49,49,50,49,49,29,24,78,78,79,29,79,29,78,78,78,23 },
		{ 0,50,64,63,64,64,64,50, 1,24,78,78,78,78,78,78,78,78,78,29 },
		{ 0,49,49,49,50,50,63,48, 1,28,78,78,78,78,29,29,78,78,78,29 },
		{ 1, 1,18, 1, 1,49,64,49, 1,29,29,79,78,78,29,79,78,78,78,29 },
		{ 9,76,76,76,18, 1,76, 1,18, 1,29,30,29,29,29,29,26,29,29,29 },
		{21,76,76,77,76,76,76,76,77,11,18,37, 9,21, 1, 9,18, 1,33, 1 },
		{ 1,77,76, 1, 1, 1,76,76,76,76,76,76,76,76,76,76,76,10,76, 1 },
		{ 1,76,76,18,76, 1,77,76,76,76,76,76,77,76,76,12,76,76,76,13 },
		{ 8, 1, 7, 1,76, 1,18, 5, 1,18,10, 1,18, 1,13,21,12,15,16, 1 }
	};

	int floor_map[20][20] = {
		{44,45,44,44,44,44,44,44,84,29,24,29,24,23,29,24, 1, 1, 1, 1},
		{44,51,52,51,51,51,51,44,84,27,85,83,83,83,83,29,23,29,83,83},
		{44,51,51,51,51,44,51,44,83,29,25,29,24,83,83,83,83,29,83,83},
		{44,51,52,51,51,45,51,44,83,83,83,29,29,83,83,83,83,25,83,83},
		{45,51,51,51,51,44,51,44,83,83,29,83,84,83,25,83,83,23,83,83},
		{44,51,51,51,51,51,52,44,83,24,83,83,83,29,29,83,83,23,29,29},
		{44,44,51,44,44,44,44,44,83,24,83,83,83,23,83,83,83,29,84,29},
		{ 1,47,84,46, 1, 1,29,29,29,29,83,83,83,83, 83,83,29,29,83,29},
		{ 1,50,83,50,49,29,31,84,83,83,83,29,29,84,83,83,29,83,83,23},
		{ 1,49,83,83,83,83,83,84,83,83,83,29,28,83,83,83,29,83,83,24},
		{ 1,50,83,49,50,29,29,29,29,83,83,83,29,29,83,29,29,83,83,23},
		{ 1,48,83,49,49,50,49,49,29,24,83,83,83,29,83,29,83, 84,83,23},
		{ 1,50,83,83,83,83,83,50,83,24,83,83,83,83,83,83,83,83,83,29},
		{ 1,49,49,49,50,50,84,48,38,28,83,84,83,83,29,29,83,83,83,29},
		{ 1, 1,18, 1, 1,49,83,49,83,29,29,83,83,83,29,83,83,83,83,29},
		{ 9,83,83, 1,18, 1,84, 1,18, 1,29,30,29,29,29,29,26,29,29,29},
		{21,83,83,83,83,84,83,83,83,11,18,37, 9,21, 1, 9,18, 1,33, 1},
		{ 1,84,83, 1, 1, 1,83,83,83,83,83,83,83,83,83,83,83,10,83, 1},
		{ 1,83,83,18, 1, 1,83,83,83,83,83,83,83,83,83,12,83,83,83,13},
		{18, 1, 7, 1, 1, 1,18, 5, 1,18,10, 1,18, 1,13,21,12,15,16, 1}
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

	int total_kills = 35;
	int total_items = 24;

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

	const int MAP_HEIGHT = 20;
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
	void level_1::show_defeat_menu();

	int player_kills = 0;
	int items_collected = 0;

public:


	std::vector<std::vector<int>> world_map {
		{44,45,44,44,44,44,44,44, 0,29,24,29,24,23,29,24, 0, 0, 0, 0},
		{44, 0, 0, 0, 0, 0, 0,44, 0,27, 0, 0, 0, 0, 0,29,23,29, 0, 0},
		{44, 0, 0, 0, 0,44, 0,44, 0,29,25,29,24, 0, 0, 0, 0,29, 0, 0},
		{44, 0, 0, 0, 0,45, 0,44, 0, 0, 0,29,29, 0, 0, 0, 0,25, 0, 0},
		{45, 0, 0, 0, 0,44, 0,44, 0, 0,29, 0, 0, 0,25, 0, 0,23, 0, 0},
		{44, 0, 0, 0, 0, 0, 0,44, 0,24, 0, 0, 0,29,29, 0, 0,23,29,29},
		{44,44,96,44,44,44,44,44, 0,24, 0, 0, 0,23, 0, 0, 0,29, 0,29},
		{ 0,47, 0,46, 0, 0,29,29,29,29, 0, 0,0, 0, 0, 0,29,29, 0,29},
		{ 0,50, 0,50,49,29,31, 0, 0, 0, 0,29,29, 0, 0, 0,29, 0, 0,23},
		{ 0,49, 0, 0,96, 0, 0, 0, 0, 0, 0,29,28, 0, 0, 0,29, 0, 0,24},
		{ 0,50, 0,49,50,29,29,29,29, 0, 0, 0,29,29, 0,29,29, 0, 0,23},
		{ 0,48, 0,49,49,50,49,49,29,24, 0, 0, 0,29, 0,29, 0, 0, 0,23},
		{ 0,50, 0, 0, 0, 0, 0,50, 0,24, 0, 0, 0, 0, 0,68, 0, 0, 0,29},
		{ 0,49,49,49,50,50, 0,48, 0,28, 0, 0, 0, 0,29,29, 0, 0, 0,29},
		{ 1, 1,18, 1, 0,49, 0,49, 0,29,29, 0, 0, 0,29, 0, 0, 0, 0,29},
		{ 9, 0, 0, 1,18, 1,96, 1,18, 1,29,30,29,29,29,29,26,29,29,29},
		{21, 0, 0, 0, 0, 0, 0, 0, 0,11,18,37, 9,21, 1, 9,18, 1,33, 1},
		{ 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,10, 0, 1},
		{ 1, 0, 0,18, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,12, 0, 0, 0,13},
		{18, 1, 7, 1, 0, 1,18, 5, 1,18,10, 1,18, 1,13,21,12,15,16, 1}
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

	CREATE_FUNC(level_1);
};