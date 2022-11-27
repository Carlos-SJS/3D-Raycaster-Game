#include "TestScene.h"
//hi a
//Textures
#include "Textures/textures.h"
#include "Sprites/sprites.h"
#include "GameData.h"

//	#include "AudioEngine.h"

USING_NS_CC;


Scene* TestScene::createScene(){
	return TestScene::create();
}

bool TestScene::init() {
	if (!Scene::init()) return false;

	//AudioEngine::uncacheAll();
	//AudioEngine::preload("audio/music/la_grange.wav");
	//AudioEngine::play2d("audio/music/la_grange.mp3");

	auto screen_size = Director::getInstance()->getVisibleSize();
	ray_count = screen_size.width/PIXEL_SIZE;


	GLViewImpl* gl_view = (GLViewImpl*)Director::getInstance()->getOpenGLView();
	gl_view->set_raw_input(true);

	//auto label = Label::createWithTTF("Cocos GOD", "fonts/Marker Felt.ttf", 24);
	//label->setPosition(Vec2(screen_size.width/2-label->getContentSize().width/2, screen_size.height / 2 - label->getContentSize().height/2));
	//this->addChild(label, 1);

	dNode = DrawNode::create();
	this->addChild(dNode, 0);

	dNodeS = DrawNode::create();
	this->addChild(dNodeS, 1);

	player_data.x = 2.3;
	player_data.y = 4;
	player_data.angle = P3;
	player_data.speed = 1.0;

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(TestScene::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(TestScene::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	auto _mouseListener = EventListenerMouse::create();
	_mouseListener->onMouseMove = CC_CALLBACK_1(TestScene::onMouseMove, this);
	_mouseListener->onMouseDown = CC_CALLBACK_1(TestScene::onMouseDown, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);


	//Sprites
	barrel1 = ebarrel::create(1.5, 1.5, (game_manager*)this);

	cdemon1 = cacodemon::create(8.5, 8.5, .15);
	zombie1 = zombie::create(1.5, 8.5);
	imp1 = imp::create(6.5, 3.5);
	impp1 = imp_projectile::create(1.5, 8.5, .5, P2, this);

	draw_list.push_back((draw_obj*)barrel1);
	draw_list.push_back((draw_obj*)cdemon1);
	draw_list.push_back((draw_obj*)zombie1);
	draw_list.push_back((draw_obj*)imp1);
	draw_list.push_back((draw_obj*)impp1);

	update_list.push_back((entity*)barrel1);
	update_list.push_back((entity*)cdemon1);
	update_list.push_back((entity*)zombie1);
	update_list.push_back((entity*)imp1);
	update_list.push_back((entity*)impp1);

	solid_obj_list.push_back((colider*)zombie1);
	solid_obj_list.push_back((colider*)cdemon1);
	solid_obj_list.push_back((colider*)imp1);
	solid_obj_list.push_back((colider*)barrel1);
	solid_obj_list.push_back((colider*)&player_data);



	depth_map.resize(screen_size.width/PIXEL_SIZE);

	//UI Shit
	Sprite* ui_main = Sprite::create("ui_main_bar.png");

	float sX = UI_WIDTH / ui_main->getContentSize().width;
	float sY = UI_HEIGHT / ui_main->getContentSize().height;
	
	ui_main->setScale(sX, sY);
	ui_main->setAnchorPoint(Vec2(0,0));
	ui_main->setPosition(Vec2(0, 0));
	this->addChild(ui_main, 15);

	weapon_s = Sprite::create("weapons/pistol/pistol1.png");
	weapon_s->setScale(0.2*(float)SCREEN_WIDTH / weapon_s->getContentSize().width, 0.2 * (float)SCREEN_HEIGHT / weapon_s->getContentSize().height);
	weapon_s->setAnchorPoint(Vec2(.5, 0));
	weapon_s->setPosition(Vec2(SCREEN_WIDTH/2.0, UI_HEIGHT));
	this->addChild(weapon_s, 10);

	face_s = Sprite::create("faces/100f.png");
	face_s->setScale(sX, sY);
	face_s->setAnchorPoint(Vec2(0, 0));
	face_s->setPosition(Vec2(0.63 * SCREEN_WIDTH, 0.025*UI_HEIGHT));
	this->addChild(face_s, 15);

	crosshair = Sprite::create("crosshair1.png");
	crosshair->setPosition(Vec2(SCREEN_WIDTH/2, UI_HEIGHT + GAME_HEIGHT/2));
	this->addChild(crosshair, 10);

	this->scheduleUpdate();

	return true;
}

void TestScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event){
	switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
		case EventKeyboard::KeyCode::KEY_W:
			key_states[UP_ARROW_KEY] = 1;
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		case EventKeyboard::KeyCode::KEY_S:
			key_states[DOWN_ARROW_KEY] = 1;
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		case EventKeyboard::KeyCode::KEY_A:
			key_states[LEFT_ARROW_KEY] = 1;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_D:
			key_states[RIGHT_ARROW_KEY] = 1;
			break;
		case EventKeyboard::KeyCode::KEY_Q:
			key_states[Q_KEY] = 1;
			break;
		case EventKeyboard::KeyCode::KEY_E:
			key_states[E_KEY] = 1;
			break;
	}
}

void TestScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	//log("Key with keycode %d released", keyCode);
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	case EventKeyboard::KeyCode::KEY_W:
		key_states[UP_ARROW_KEY] = 0;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case EventKeyboard::KeyCode::KEY_S:
		key_states[DOWN_ARROW_KEY] = 0;
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_A:
		key_states[LEFT_ARROW_KEY] = 0;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_D:
		key_states[RIGHT_ARROW_KEY] = 0;
		break;
	case EventKeyboard::KeyCode::KEY_Q:
		key_states[Q_KEY] = 0;
		break;
	case EventKeyboard::KeyCode::KEY_E:
		key_states[E_KEY] = 0;
		break;
	}
}

void TestScene::onMouseMove(EventMouse* e){
	delta_mouse -= e->getCursorX();
}

void TestScene::onMouseDown(EventMouse* e) {
	if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) handle_player_shot();
}

std::string TestScene::to_string(float f) {
	std::ostringstream s;
	s << f;
	return s.str().c_str();
}

void TestScene::draw_rect(float x, float y, float width, float height, Color4F color) {
	Vec2 rectangle[4];

	rectangle[0] = Vec2((int)x, (int)y);
	rectangle[1] = Vec2((int)(x + width), (int)y);
	rectangle[2] = Vec2((int)(x + width), (int)(y - height));
	rectangle[3] = Vec2((int)x, (int)(y - height));

	dNode->drawPolygon(rectangle, 4, color, 1, color);
}

bool TestScene::inside(float x, float y) {
	return x >= 0 && y >= 0 && x < MAP_WIDTH&& y < MAP_HEIGHT;
}

void TestScene::draw_world() {
	auto screen_size = Director::getInstance()->getVisibleSize();
	screen_size.height = GAME_HEIGHT;
	screen_size.height /= PIXEL_SIZE;
	screen_size.width /= PIXEL_SIZE;

	float cangle = player_data.angle + fov/2 + 0.0000001;
	float step = fov/ray_count;

	float w_width = (float)screen_size.width / (float)ray_count;

	for (int r = 0; r < ray_count; r++) {

		float player_ray_angle = player_data.angle - cangle;
		if (player_ray_angle < 0) player_ray_angle += 2 * PI;
		if (player_ray_angle > 2 * PI) player_ray_angle -= 2 * PI;
		float cospa = cos(player_ray_angle);

		if (cangle < 0.0) cangle += 2 * PI;
		if (cangle >= 2 * PI) cangle -= 2 * PI;

		float at = tan(cangle);
		float dx, dy, cx, cy;

		//Check vertical lines

		cy = player_data.y;

		if (cangle<P2 || cangle>P3) {
			if (player_data.x - (int)player_data.x > eps) cx = (int)(player_data.x + 1);
			else cx = (int)player_data.x;

			cy -= (cx - player_data.x) * at;

			dx = 1.0;
		}

		if (cangle > P2 && cangle < P3) {
			if ((int)(player_data.x - 1) - player_data.x > eps) cx = (int)(player_data.x - 1) - .000001;
			else cx = (int)player_data.x - .000001;

			cy -= (cx - player_data.x) * at;

			dx = -1.0;
		}

		dy = -at*dx;

		Vec2 vc;
		bool vc_f = 0;

		if (cangle != PI && cangle != 0) {
			while (inside(cx, cy)) {
				if (world_map[(int)cy][(int)cx] > 0) {
					vc = Vec2(cx, cy);

					vc_f = 1;
					break;
				}

				cx += dx;
				cy += dy;
			}
		}


		//Check horizontal lines

		cx = player_data.x;

		if (cangle < PI && cangle>0) {
			if ((int)(player_data.y - 1) - player_data.y > eps) cy = (int)(player_data.y - 1) - .000001;
			else cy = (int)player_data.y - .000001;

			cx += (player_data.y - cy)/at;

			dy = -1.0;
		}

		if (cangle > PI || cangle < 0) {
			if (player_data.y - int(player_data.y) > eps)  cy = (int)(player_data.y + 1);
			else cy = (int)player_data.y;

			cx += (player_data.y - cy) / at;

			dy = 1.0;

		}

		Vec2 hz;
		bool hz_f = 0;

		dx = -dy / at;

		if (cangle != P2 && cangle != P3) {
			while (inside(cx, cy)) {
				if (world_map[(int)cy][(int)cx] > 0) {
					hz = Vec2(cx, cy);

					hz_f = 1;
					break;
				}

				cx += dx;
				cy += dy;
			}
		}

		//Draw better
		float distV = 0, distH = 0;

		if (vc_f) {
			//dx = player_data.x - vc.x;
			//dy = player_data.y - vc.y;
			//distV = sqrt(dx * dx + dy * dy);
			distV = cos(cangle)*(vc.x-player_data.x) - sin(cangle)*(vc.y-player_data.y);

		}

		if (hz_f) {
			//dx = player_data.x - hz.x;
			//dy = player_data.y - hz.y;
			//distH = sqrt(dx * dx + dy * dy);
			distH = cos(cangle) * (hz.x - player_data.x) - sin(cangle) * (hz.y - player_data.y);
		}

		if (vc_f && hz_f) {
			if (distV < distH) hz_f = 0;
			else vc_f = 0;
		}



		int w_height = 0;

		Vec2 points[2000];
		Color4F colors[2000];

		//Draw the vertical wall
		if (vc_f) {
			depth_map[r] = distV;

			w_height = (screen_size.height) / (distV * cospa);


			float shading = .6;
			int texture_x = (int)((vc.y - (int)vc.y) * 64);
			float texture_y = 0;
			float texture_y_step = (63.0 / w_height);

			if (w_height > screen_size.height) {
				texture_y = (float)((w_height - screen_size.height) / 2.0) * texture_y_step;
				w_height = screen_size.height;
			}

			int x = r, y = screen_size.height / 2 + w_height / 2;
			
			int t = world_map[(int)vc.y][(int)vc.x] - 1;

			for (int h = 0; h < w_height; h++) {
				points[h] = Vec2(x, SCREEN_DIFF + y - h);

				int t_index;

				if (cangle < P2 || cangle > P3) t_index = (int)texture_y * 64 * 3 + texture_x * 3;
				else t_index = (int)texture_y * 64 * 3 + 63 * 3 - texture_x * 3;

				colors[h] = Color4F((float)textures[t][t_index] / 256.0 * shading, (float)textures[t][t_index + 1] / 256.0 * shading, (float)textures[t][t_index + 2] / 256.0 * shading, 1);

				texture_y += texture_y_step;
			}

			//draw_rect(r * w_width, screen_size.height/2 + w_height/2, w_width, w_height, Color4F(0.9,0,0,1));
		}

		//Draw the horizontal wall
		if (hz_f) {
			depth_map[r] = distH;

			w_height = (screen_size.height) / (distH * cospa);

			float shading = 1;
			int texture_x = (int)((hz.x - (int)hz.x) * 64);
			float texture_y = 0;
			float texture_y_step = (63.0 / w_height);

			if (w_height > screen_size.height) {
				texture_y = (float)(w_height - screen_size.height) / 2.0 * texture_y_step;
				w_height = screen_size.height;
			}


			int x = r, y = screen_size.height / 2 + w_height / 2;

			int t = world_map[(int)hz.y][(int)hz.x] - 1;

			for (int h = 0; h < w_height; h++) {
				points[h] = Vec2(x, SCREEN_DIFF + y - h);

				int t_index;

				if (cangle > 0 && cangle < PI) t_index = (int)texture_y * 64 * 3 + texture_x * 3;
				else t_index = (int)texture_y * 64 * 3 + 63*3 - texture_x * 3;

				colors[h] = Color4F((float)textures[t][t_index] / 256.0 * shading, (float)textures[t][t_index + 1] / 256.0 * shading, (float)textures[t][t_index + 2] / 256.0 * shading, 1);

				texture_y += texture_y_step;
			}

			vc.x = hz.x;
			vc.y = hz.y;

			//draw_rect(r * w_width, screen_size.height / 2 + w_height / 2, w_width, w_height, Color4F(0.6, 0, 0, 1));
		}


		//Draw floor and ceiling
		int fx = vc.x;

		//Precalculate stuff
		float sina = sin(cangle);
		float cosa = cos(cangle);

		int c = 0;

		for (int y = screen_size.height / 2.0 - w_height / 2.0 - 1; y >= 0; y--, c+=2) {
			//Calculate texture indexes
			float dy = screen_size.height / (2.0 * ( - y) + screen_size.height);
			float ftx = (player_data.x + cosa * dy / cospa);
			float fty = (player_data.y - sina * dy / cospa);

			int ft = floor_map[(int)fty][(int)ftx] - 1;
			int ct = ceiling_map[(int)fty][(int)ftx] - 1;

			int tx = (int) (64.0*ftx);
			int ty = (int) (64.0*fty);



			tx &= 63;
			ty &= 63;

			int texture_index = ty * 64 * 3 + tx * 3;

			//Draw floor
			points[w_height + c] = Vec2(r, SCREEN_DIFF + y);
			colors[w_height + c] = Color4F(((float)textures[ft][texture_index]) / 255.0, ((float)textures[ft][texture_index + 1]) / 255.0, ((float)textures[ft][texture_index + 2]) / 255.0, 1.0);

			//Draw ceiling
			points[w_height + c + 1] = Vec2(r, SCREEN_DIFF + screen_size.height - y);
			colors[w_height + c + 1] = Color4F(((float)textures[ct][texture_index]) / 255.0, ((float)textures[ct][texture_index + 1]) / 255.0, ((float)textures[ct][texture_index + 2]) / 255.0, 1.0);
		}

		dNode->drawPoints(points, screen_size.height, PIXEL_SIZE, colors);

		/*log(("-- Data ----------- (" + to_string((float)r) + ")").c_str());
		log(("Current Angle: " + to_string(cangle)).c_str());
		log(("Player Position: " + to_string(player_data.x) + ", " + to_string(player_data.y)).c_str());
		log(("Horizontal colition ( " + to_string(distH) + "): " + to_string(hz.x) + ", " + to_string(hz.y)).c_str());
		log(("Vertical colition (" + to_string(distV) + "): " + to_string(vc.x) + ", " + to_string(vc.y)).c_str());*/

		cangle -= step;
	}
	//log("Done");
}

void TestScene::handle_input(float dt) {
    float wdist = .2;
	float sdist = 0;

	if (key_states[UP_ARROW_KEY]) {
		float c = cos(player_data.angle);
		float s = sin(player_data.angle);

		float dx = c * player_data.speed * dt;
		float dy = s * player_data.speed * dt;

		if (world_map[(int)player_data.y][(int)(player_data.x + dx + c * .4)] == 0 && get_objs(player_data.x + dx, player_data.y, 0, .3).size() < 2) player_data.x += dx;
		if (world_map[(int)(player_data.y - dy - s * .4)][(int)player_data.x] == 0 && get_objs(player_data.x, player_data.y - dy, 0, .3).size() < 2) player_data.y -= dy;
	}
	if (key_states[DOWN_ARROW_KEY]) {
		float c = cos(player_data.angle);
		float s = sin(player_data.angle);

		float dx = c * player_data.speed * dt;
		float dy = s * player_data.speed * dt;

		if (world_map[(int)player_data.y][(int)(player_data.x - dx - c * wdist)] == 0 && get_objs(player_data.x - dx, player_data.y, 0, .3).size()<2) player_data.x -= dx;
		if (world_map[(int)(player_data.y + dy + s * wdist)][(int)player_data.x] == 0 && get_objs(player_data.x, player_data.y + dy, 0, .3).size() < 2) player_data.y += dy;
	}
	if (key_states[RIGHT_ARROW_KEY]) {
		float c = cos(player_data.angle - P2);
		float s = sin(player_data.angle - P2);

		float dx = c * player_data.speed * dt;
		float dy = s * player_data.speed * dt;

		if (world_map[(int)player_data.y][(int)(player_data.x + dx + c * wdist)] == 0 && get_objs(player_data.x + dx, player_data.y, 0, .3).size() < 2) player_data.x += dx;
		if (world_map[(int)(player_data.y - dy - s * wdist)][(int)player_data.x] == 0 && get_objs(player_data.x, player_data.y - dy, 0, .3).size() < 2) player_data.y -= dy;
	}
	if (key_states[LEFT_ARROW_KEY]) {
		float c = cos(player_data.angle + P2);
		float s = sin(player_data.angle + P2);

		float dx = c * player_data.speed * dt;
		float dy = s * player_data.speed * dt;

		if (world_map[(int)player_data.y][(int)(player_data.x + dx + c * wdist)] == 0 && get_objs(player_data.x + dx, player_data.y, 0, .3).size() < 2)player_data.x += dx;
		if (world_map[(int)(player_data.y - dy - s * wdist)][(int)player_data.x] == 0 && get_objs(player_data.x, player_data.y - dy, 0, .3).size() < 2)player_data.y -= dy;
	}

	/*if (key_states[Q_KEY]) {
		player_data.angle += 1 * dt;
		if (player_data.angle >= 2 * PI) player_data.angle -= 2 * PI;
	}
	if (key_states[E_KEY]) {
		player_data.angle -= 1 * dt;
		if (player_data.angle < 0.0) player_data.angle += 2 * PI;
	}*/

	if (abs(delta_mouse) > 7) {
		if (delta_mouse > 0) face_s->setTexture("faces/100l.png");
		else face_s->setTexture("faces/100r.png");
		face_cooldown = .1;
	}
	else {
		if (face_cooldown > 0) face_cooldown -= dt;
		else face_s->setTexture("faces/100f.png");
	}

	if (delta_mouse != 0.0) {
				player_data.angle += 0.001 * delta_mouse;
		delta_mouse = 0;

		if (player_data.angle >= 2 * PI) player_data.angle -= 2 * PI;
		if (player_data.angle < 0.0) player_data.angle += 2 * PI;
	}
}

float fix(float a) {
	if (a < 0) return a + 2*PI;
	if (a > 2 * PI) return a - 2 * PI;
	return a;
}

void TestScene::schedule_sprite(better_sprite* sprite) {
	Vec2 pos = sprite->get_position();

	float dx = (pos.x - player_data.x);
	float dy = (player_data.y - pos.y);
	float a = angle_util::get_angle(dx, dy);

	float dist = sqrt(dx * dx + dy * dy);

	sprite_queue.push(buffered_sprite(dist, a, sprite));
}

void TestScene::draw_sprites() {
	while (!sprite_queue.empty()) {
		draw_sprite(sprite_queue.top().dist, sprite_queue.top().angle, sprite_queue.top().sprite);
		sprite_queue.pop();
	}
}

void TestScene::draw_sprite(float dist, float a, better_sprite* sprite) {
	auto screen_size = Director::getInstance()->getWinSize();	

	screen_size.height = GAME_HEIGHT;
	screen_size.height /= PIXEL_SIZE;
	screen_size.width /= PIXEL_SIZE;

	float pa = player_data.angle + fov / 2;
	pa = angle_util::fix(pa);

	//float cospa = cos(angle_util::fix(player_data.angle - a));
	float cospa = cos(angle_util::fix(a-player_data.angle));

	//if (dist < .74) return;

	float unit_size = (screen_size.height) / (dist * cospa);

	float swidth = sprite->get_sx() * unit_size;
	float sheight = sprite->get_sy() * unit_size;

	Vec2 point_buffer[2000];
	Color4F color_buffer[2000];
	int point_count = 0;

	//if (a > pa) a -= 2*PI;
	float x;

	if(abs((pa)-a) < abs((pa)-a + 2.0*PI)) x = ((pa)-a) / (fov / ray_count) - swidth / 2.0;
	else x = ((pa)-(a - 2.0 * PI))  / (fov / ray_count) - swidth / 2.0;


	float xoffset = 0;

	if (x < 0 && x + swidth >= 0) {
		xoffset = -x;
	}

	float ground = screen_size.height/2 - unit_size/2;
	float y = ground + sprite->get_z()*unit_size;
	float yoffset = 0;
	
	if (y < 0 && y + sheight >= 0) {
		yoffset = -y;
	}
	
	int* texture = sprite->get_texture();
	
	int tsx = sprite->get_tsize().x;
	int tsy = sprite->get_tsize().y;

	float xstep = (float)(tsx-1)/swidth;
	float ystep = (float)(tsy-1)/sheight;

	int tindex;

	if (x < screen_size.width && x+xoffset >= 0) {
		for (int i = (int)xoffset; i < swidth && x + i < screen_size.width; i+=1.0) {
			if (depth_map[(int)(x + i)] >= dist) {
				//depth_map[(int)(x + i)] = dist;

				for (int j = yoffset; j < sheight && y + j < screen_size.height; j+=1.0) {
					tindex = (int)((float)(tsy-1) - ystep * (float)j) * tsx * 3 + (int)((float)i * xstep) * 3;

					if (texture[tindex] != 0 || texture[tindex + 1] != 255 || texture[tindex + 2] != 255) {
						point_buffer[point_count] = Vec2((int)(x + i), SCREEN_DIFF + (int)(y + j));
						color_buffer[point_count] = Color4F((float)texture[tindex] / 255.0, (float)texture[tindex + 1] / 255.0, (float)texture[tindex + 2] / 255.0, 1);
						point_count++;
					}
				}
				if (point_count > 2000 - screen_size.height) {
					dNodeS->drawPoints(point_buffer, point_count, (float)PIXEL_SIZE, color_buffer);
					point_count = 0;
				}
			}
		}

		if (point_count > 0) dNodeS->drawPoints(point_buffer, point_count, PIXEL_SIZE, color_buffer);
	}
}

void TestScene::handle_sprites() {

}

void TestScene::update(float dt) {
	//Player movement
	handle_input(dt);

	//Update entities
	int inc=1;
	for (auto sp = update_list.begin(); sp != update_list.end(); sp+=inc) {
		if (!inc) inc = 1;
		if (!(*sp)->update(dt, &player_data, world_map)) {
			sp = update_list.erase(sp);
			inc = 0;
		}
	}

	targets = get_targets(player_data.x, player_data.y, player_data.angle);
	
	player_animator(dt);

	//Reset draw node
	dNode->clear();
	dNodeS->clear();

	inc = 1;
	for (auto sp = draw_list.begin(); sp != draw_list.end(); sp+=inc) {
		if (!inc) inc = 1;
		if((*sp)->is_visible()) schedule_sprite((*sp)->get_sprite());
		else sp = draw_list.erase(sp), inc=0;
	}


	draw_sprites();

	//Draw world
	draw_world();
}

std::priority_queue<target_entity> TestScene::get_targets(float x, float y, float a) {
	float at = tan(a);
	float dx, dy, cx, cy, wall_d = 5000000;

	int inc = 1;
	for (auto it = solid_obj_list.begin(); it != solid_obj_list.end(); it+=inc) {
		if (!inc) inc = 1;
		if (!(*it)->is_solid()) it = solid_obj_list.erase(it), inc = 0;
	}

	cy = y;
	if (a<P2 || a>P3) {
		if (x - (int)x > eps) cx = (int)(x + 1);
		else cx = (int)x;

		cy -= (cx - x) * at;

		dx = 1.0;
	}
	if (a > P2 && a < P3) {
		if ((int)(x) - x > eps) cx = (int)(x - 1) - .000001;
		else cx = (int)x - .000001;

		cy -= (cx - x) * at;

		dx = -1.0;
	}

	dy = -at * dx;

	if (a != PI && a != 0) {
		while (inside(cx, cy)) {
			if (world_map[(int)cy][(int)cx] > 0) {
				cx -= x; cy -= y;
				wall_d = sqrt(cx*cx + cy*cy);
				break;
			}

			cx += dx;
			cy += dy;
		}
	}

	cx = x;
	if (a < PI && a>0) {
		if ((int)(y - 1) - y > eps) cy = (int)(y - 1) - .000001;
		else cy = (int)y - .000001;

		cx += (y - cy) / at;

		dy = -1.0;
	}

	if (a > PI || a < 0) {
		if (y - int(y) > eps)  cy = (int)(y + 1);
		else cy = (int)y;

		cx += (y - cy) / at;

		dy = 1.0;

	}

	dx = -dy / at;

	if (a != P2 && a != P3) {
		while (inside(cx, cy)) {
			if (world_map[(int)cy][(int)cx] > 0) {
				cx -= x;cy -= y;
				wall_d = min(sqrt(cx*cx + cy*cy), wall_d);
				break;
			}

			cx += dx;
			cy += dy;
		}
	}

	float dist, size, ewidth, ex, ea, cospa, sinpa;
	Vec3 pos;

	std::priority_queue<target_entity> target_list;

	for (auto obj : solid_obj_list) {
		pos = obj->get_pos();
		dx = pos.x - x, dy = y - pos.y;

		ea = angle_util::get_angle(dx, dy);

		sinpa = sin(angle_util::fix(a - ea));
		//cospa = cos(angle_util::fix(a - ea));
		cospa = cos(angle_util::fix(ea-a));

		dist = sqrt(dx * dx + dy * dy);

		size = 1 / (dist * cospa);

		ewidth = obj->get_rect().x * size;

		if (dist > .2 && abs(a-ea)<P2 &&  dist < wall_d && abs(dist * sinpa) < obj->get_rect().x / 2 * .8) {
			target_list.push(target_entity(obj, dist));
		}
	}

	return target_list;
}

void TestScene::player_animator(float dt) {
	if (weapon_cooldown) {
		weapon_anim_timer += dt;

		if (weapon_anim_timer >= weapon_f_time[weapon_id][weapon_frame]) {
			weapon_anim_timer = 0;
			weapon_frame++;

			if(weapon_frame == weapon_textures[weapon_id].size()-1) weapon_cooldown = 0;

			weapon_s->setTexture(weapon_textures[weapon_id][weapon_frame]);
		}
	}

	if (targets.empty() && crosshair_mode == 1) {
		crosshair_mode = 0;
		crosshair->setTexture("crosshair1.png");
	}
	else if (!targets.empty() && crosshair_mode == 0) {
		crosshair_mode = 1;
		crosshair->setTexture("crosshair2.png");
	}
}

void TestScene::handle_player_shot() {
	if (!weapon_cooldown) {
		weapon_cooldown = 1;
		weapon_anim_timer = 0;
		weapon_frame = 0;

		weapon_s->setTexture(weapon_textures[weapon_id][0]);

		if (targets.empty()) return;

		if (weapon_id == 0) {

		}
		else if (weapon_id == 1) {
			targets.top().obj->handle_collision(weapon_damage[weapon_id]);
		}

	}
}

std::vector<colider*> TestScene::get_objs(float x, float y, float z, float radius) {
	int inc = 1;
	for (auto obj = solid_obj_list.begin(); obj != solid_obj_list.end(); obj += inc) {
		if (inc == 0) inc = 1;
		if (!(*obj)->is_solid()) {
			obj = solid_obj_list.erase(obj), inc = 0;
			log("obj removed from solids list!");
		}
	}

	float radius2 = radius*radius;

	cocos2d::Vec3 pos;
	cocos2d::Vec2 rect;
	float dx, dy, dz, dist, d;

	std::vector<colider*>  obj_list;

	for (auto obj : solid_obj_list) {
		pos = obj->get_pos();
		rect = obj->get_rect();

		dx = x - pos.x;
		dy = y - pos.y;

		dist = dx * dx + dy * dy;



		if (dist <= radius2 + rect.x* rect.x / 4) {
			dz = z+radius - (pos.z + rect.y/2);

			if (abs(dz) < radius + rect.y / 2) {
				obj_list.push_back(obj);
			}
		}

	}

	return obj_list;
}

void TestScene::handle_explosion(float x, float y, float z, float radius, int damage) {
	std::vector<colider*> objs = get_objs(x, y, z, radius);
	for (auto obj : objs) {
		obj -> handle_collision(damage);
	}
}