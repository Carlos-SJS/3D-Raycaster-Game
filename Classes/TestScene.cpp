#include "TestScene.h"

//Textures
#include "Textures/wall_1.h"
#include "Textures/floor_1.h"
#include "Textures/floor_2.h"


USING_NS_CC;


Scene* TestScene::createScene(){
	return TestScene::create();
}

bool TestScene::init() {
	if (!Scene::init()) return false;

	auto screen_size = Director::getInstance()->getVisibleSize();
	ray_count = screen_size.width;


	GLViewImpl* gl_view = (GLViewImpl*)Director::getInstance()->getOpenGLView();
	gl_view->set_raw_input(true);

	//auto label = Label::createWithTTF("Cocos GOD", "fonts/Marker Felt.ttf", 24);
	//label->setPosition(Vec2(screen_size.width/2-label->getContentSize().width/2, screen_size.height / 2 - label->getContentSize().height/2));
	//this->addChild(label, 1);

	dNode = DrawNode::create();
	this->addChild(dNode, 0);

	player_data.x = 1;
	player_data.y = 1;
	player_data.angle = P2;
	player_data.speed = 1.0;

	log("This is a test log!");

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(TestScene::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(TestScene::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	
	auto _mouseListener = EventListenerMouse::create();
	_mouseListener->onMouseMove = CC_CALLBACK_1(TestScene::onMouseMove, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);



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

int min(int x, int y) {
	return x < y ? x : y;
}

void TestScene::draw_world() {
	auto screen_size = Director::getInstance()->getVisibleSize();

	float cangle = player_data.angle + fov/2 + 0.0000001;
	float step = fov/ray_count;

	float w_width = (float)screen_size.width / (float)ray_count;

	for (int r = 0; r < ray_count; r++) {

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
				if (world_map[(int)cy][(int)cx] != 0) {
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
				if (world_map[(int)cy][(int)cx] != 0) {
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
			w_height = (screen_size.height) / (distV * cos(player_data.angle - cangle));


			float shading = .6;
			int texture_x = (int)((vc.y - (int)vc.y) * 64);
			float texture_y = 0;
			float texture_y_step = (63.0 / w_height);

			if (w_height > screen_size.height) {
				texture_y = (float)(w_height - screen_size.height) / 2.0 * texture_y_step;
				w_height = screen_size.height;
			}

			int x = r, y = screen_size.height / 2 + w_height / 2;

			for (int h = 0; h < w_height; h++) {
				points[h] = Vec2(x, y - h);

				int t_index;

				if (cangle < P2 || cangle > P3) t_index = (int)texture_y * 64 * 3 + texture_x * 3;
				else t_index = (int)texture_y * 64 * 3 + 63 * 3 - texture_x * 3;

				colors[h] = Color4F((float)wall_1[t_index] / 256.0 * shading, (float)wall_1[t_index] / 256.0 * shading, (float)wall_1[t_index] / 256.0 * shading, 1);

				texture_y += texture_y_step;
			}

			//draw_rect(r * w_width, screen_size.height/2 + w_height/2, w_width, w_height, Color4F(0.9,0,0,1));
		}

		//Draw the horizontal wall
		if (hz_f) {
			w_height = (screen_size.height) / (distH * cos(player_data.angle - cangle));

			float shading = 1;
			int texture_x = (int)((hz.x - (int)hz.x) * 64);
			float texture_y = 0;
			float texture_y_step = (63.0 / w_height);

			if (w_height > screen_size.height) {
				texture_y = (float)(w_height - screen_size.height) / 2.0 * texture_y_step;
				w_height = screen_size.height;
			}
			

			int x = r, y = screen_size.height / 2 + w_height / 2;

			for (int h = 0; h < w_height; h++) {
				points[h] = Vec2(x, y - h);
				
				int t_index;

				if (cangle > 0 && cangle < PI) t_index = (int)texture_y * 64 * 3 + texture_x * 3;
				else t_index = (int)texture_y * 64 * 3 + 63*3 - texture_x * 3;

				colors[h] = Color4F((float)wall_1[t_index] / 256.0 * shading, (float)wall_1[t_index] / 256.0 * shading, (float)wall_1[t_index] / 256.0 * shading, 1);

				texture_y += texture_y_step;
			}

			vc.x = hz.x;
			vc.y = hz.y;
				
			//draw_rect(r * w_width, screen_size.height / 2 + w_height / 2, w_width, w_height, Color4F(0.6, 0, 0, 1));
		}


		//Draw floor
		int fx = vc.x;

		float sina = sin(cangle);
		float cosa = cos(cangle);
		float a = player_data.angle - cangle;
		if (a < 0) a += 2 * PI;
		if (a > 2 * PI) a -= 2 * PI;
		float cospa = cos(a);

		int c = 0;

		for (int y = screen_size.height / 2.0 - w_height / 2.0 - 1; y >= 0; y--, c+=2) {
			/*float dy = screen_size.height - (float)y - 640/2.0;
			int tx = (int)(player_data.x*64.0 + (cosa*158.0*64.0/dy/cospa ));
			int ty = (int)(player_data.y*64.0 - (sina*158.0*64.0/dy/cospa ));

			tx &= 63;
			ty &= 63;

			int texture_index = ty * 64 * 3 + tx * 3;*/

			float dy = screen_size.height / (2.0 * (screen_size.height - y) - screen_size.height);
			int tx = (int)(player_data.x * 64.0 + cosa * dy * 64.0 / cospa);
			int ty = (int)(player_data.y * 64.0 - sina * dy * 64.0 / cospa);

			tx &= 63;
			ty &= 63;

			int texture_index = ty * 64 * 3 + tx * 3;

			points[w_height + c] = Vec2(r, y);
			colors[w_height + c] = Color4F(((float)floor_1[texture_index]) / 255.0, ((float)floor_1[texture_index + 1]) / 255.0, ((float)floor_1[texture_index + 2]) / 255.0, 1.0);

			points[w_height + c + 1] = Vec2(r, screen_size.height - y);
			colors[w_height + c + 1] = Color4F(((float)floor_2[texture_index]) / 255.0, ((float)floor_2[texture_index + 1]) / 255.0, ((float)floor_2[texture_index + 2]) / 255.0, 1.0);
		}

		dNode->drawPoints(points, screen_size.height, colors);

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
	if (key_states[UP_ARROW_KEY]) {
		float c = cos(player_data.angle);
		float s = sin(player_data.angle);

		float dx = c * player_data.speed * dt;
		float dy = s * player_data.speed * dt;

		if (world_map[(int)player_data.y][(int)(player_data.x + dx + c * .1)] == 0) player_data.x += dx;
		if (world_map[(int)(player_data.y - dy - s * .1)][(int)player_data.x] == 0) player_data.y -= dy;
	}
	if (key_states[DOWN_ARROW_KEY]) {
		float c = cos(player_data.angle);
		float s = sin(player_data.angle);

		float dx = c * player_data.speed * dt;
		float dy = s * player_data.speed * dt;

		if (world_map[(int)player_data.y][(int)(player_data.x - dx - c * .1)] == 0) player_data.x -= dx;
		if (world_map[(int)(player_data.y + dy + s * .1)][(int)player_data.x] == 0) player_data.y += dy;
	}
	if (key_states[RIGHT_ARROW_KEY]) {
		float c = cos(player_data.angle - P2);
		float s = sin(player_data.angle - P2);

		float dx = c * player_data.speed * dt;
		float dy = s * player_data.speed * dt;

		if (world_map[(int)player_data.y][(int)(player_data.x + dx + c * .1)] == 0) player_data.x += dx;
		if (world_map[(int)(player_data.y - dy - s * .1)][(int)player_data.x] == 0) player_data.y -= dy;
	}
	if (key_states[LEFT_ARROW_KEY]) {
		float c = cos(player_data.angle + P2);
		float s = sin(player_data.angle + P2);

		float dx = c * player_data.speed * dt;
		float dy = s * player_data.speed * dt;

		if (world_map[(int)player_data.y][(int)(player_data.x + dx + c * .1)] == 0)player_data.x += dx;
		if (world_map[(int)(player_data.y - dy - s * .1)][(int)player_data.x] == 0)player_data.y -= dy;
	}

	/*if (key_states[Q_KEY]) {
		player_data.angle += 1 * dt;
		if (player_data.angle >= 2 * PI) player_data.angle -= 2 * PI;
	}
	if (key_states[E_KEY]) {
		player_data.angle -= 1 * dt;
		if (player_data.angle < 0.0) player_data.angle += 2 * PI;
	}*/

	if (delta_mouse != 0.0) {
		player_data.angle += 0.001 * delta_mouse;
		delta_mouse = 0;

		if (player_data.angle >= 2 * PI) player_data.angle -= 2 * PI;
		if (player_data.angle < 0.0) player_data.angle += 2 * PI;
	}
}

void TestScene::update(float dt) {
	//Player movement
	handle_input(dt);

	//Reset draw node
	dNode->clear();

	//Draw world
	draw_world();
}