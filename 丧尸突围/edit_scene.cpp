#include "edit_scene.h"

#include "level_mgr.h"
#include "scene_mgr.h"
#include "enemy_ins.h"
#include "item_ins.h"

#include <fstream>

extern bool DEBUG;

bool EditScene::mouse_in_box(CollisionBox* box) {
	Vector2 box_pos = box->get_pos() - window_pos;
	Vector2 box_size = box->get_size();
    return mouse_pos.x >= box_pos.x - box_size.x / 2 && mouse_pos.x <= box_pos.x + box_size.x / 2 &&
        mouse_pos.y >= box_pos.y - box_size.y / 2 && mouse_pos.y <= box_pos.y + box_size.y / 2;
}

void EditScene::on_enter() {
	// 设置编辑关卡
	LevelMgr::instance()->load_level(1);

	timer_generate.set_wait_time(1.0f);
	timer_generate.set_on_timeout([&]() {
		is_generating = false;
		});
}

void EditScene::on_update(float delta) {
	// 敌人状态机不能进行更新 需要手动关闭  enemy.cpp -> state_machine.on_update(delta);
	LevelMgr::instance()->on_update(delta);

	timer_generate.on_update(delta);
	// 更新鼠标位置
	int x, y;
	SDL_GetMouseState(&x, &y);
	mouse_pos = Vector2(x, y);
}

void EditScene::on_render(Camera& camera) {
	camera.set_pos(window_pos);

	// 背景
	SDL_Color bg_color{ 0,255,255,255 };
	SDL_Rect rect{
		0,0,
		1280,720
	};
	camera.fill_rect(&rect, bg_color);

	LevelMgr::instance()->on_render(camera);

	// DEBUG 碰撞箱
	CollisionMgr::instance()->on_debug_render(camera);
}

void EditScene::on_input(const SDL_Event& msg) {
	/*
	键盘从 1 开始为Item
	小键盘从 0 开始为Enemy
	鼠标左键选中物品
	ENTER 保存文件方便创建关卡
	BACK 删除物品
	*/
	if (!is_generating && msg.type == SDL_KEYDOWN) {
		switch (msg.key.keysym.sym) {
		case SDLK_1:	LevelMgr::instance()->add_item(new notebook(window_pos + mouse_pos));			break;
		case SDLK_2:	LevelMgr::instance()->add_item(new BoxCat(window_pos + mouse_pos));				break;
		case SDLK_3:	LevelMgr::instance()->add_item(new bush(window_pos + mouse_pos));				break;
		case SDLK_4:	LevelMgr::instance()->add_item(new rock_1(window_pos + mouse_pos));				break;
		case SDLK_5:	LevelMgr::instance()->add_item(new rock_2(window_pos + mouse_pos));				break;
		case SDLK_6:	LevelMgr::instance()->add_item(new rock_3(window_pos + mouse_pos));				break;
		case SDLK_7:	LevelMgr::instance()->add_item(new sleepBlackCat(window_pos + mouse_pos));		break;
		case SDLK_8:	LevelMgr::instance()->add_item(new stone1(window_pos + mouse_pos));				break;
		case SDLK_9:	LevelMgr::instance()->add_item(new stone2(window_pos + mouse_pos));				break;
		case SDLK_a:	LevelMgr::instance()->add_item(new streelight(window_pos + mouse_pos));			break;
		case SDLK_b:	LevelMgr::instance()->add_item(new stump(window_pos + mouse_pos));				break;
		case SDLK_c:	LevelMgr::instance()->add_item(new tree1(window_pos + mouse_pos));				break;
		case SDLK_d:	LevelMgr::instance()->add_item(new trunk(window_pos + mouse_pos));				break;
		case SDLK_e:	LevelMgr::instance()->add_item(new YellowCat(window_pos + mouse_pos));			break;
		case SDLK_f:	LevelMgr::instance()->add_item(new background(window_pos + mouse_pos));			break;
		case SDLK_g:	LevelMgr::instance()->add_item(new sunsetbackground(window_pos + mouse_pos));	break;
		case SDLK_h:	LevelMgr::instance()->add_item(new background_layer(window_pos + mouse_pos));	break;
		case SDLK_i:	LevelMgr::instance()->add_item(new cloud_1(window_pos + mouse_pos));			break;
		case SDLK_j:	LevelMgr::instance()->add_item(new cloud_2(window_pos + mouse_pos));			break;
		case SDLK_k:	LevelMgr::instance()->add_item(new cloud_3(window_pos + mouse_pos));			break;


		case SDLK_KP_0:	LevelMgr::instance()->add_enemy(new FlyingEye(window_pos + mouse_pos));			break;
		case SDLK_KP_1:	LevelMgr::instance()->add_enemy(new Goblin(window_pos + mouse_pos));			break;
		case SDLK_KP_2:	LevelMgr::instance()->add_enemy(new Mushroom(window_pos + mouse_pos));			break;
		case SDLK_KP_3:	LevelMgr::instance()->add_enemy(new Skeleton(window_pos + mouse_pos));			break;
		case SDLK_KP_4:	LevelMgr::instance()->add_enemy(new SpriteSheets(window_pos + mouse_pos));		break;
		case SDLK_KP_5:	LevelMgr::instance()->add_enemy(new Ninja(window_pos + mouse_pos));				break;
		case SDLK_KP_6:	LevelMgr::instance()->add_enemy(new Minotaur(window_pos + mouse_pos));			break;
		case SDLK_KP_7:	LevelMgr::instance()->add_enemy(new Slime1(window_pos + mouse_pos));			break;
		case SDLK_KP_8:	LevelMgr::instance()->add_enemy(new Slime2(window_pos + mouse_pos));			break;
		}

		is_generating = true;
	}

	switch (msg.type) {
	case SDL_KEYDOWN: 
	{
		if (is_select) {
			Vector2 move_axis;
			switch (msg.key.keysym.sym) {
			case SDLK_UP:	move_axis.y -= 10;		break;
			case SDLK_DOWN: move_axis.y += 10;		break;
			case SDLK_LEFT: move_axis.x -= 10;		break;
			case SDLK_RIGHT:move_axis.x += 10;		break;

			case SDLK_BACKSPACE:
			{
				if (selected_enemy) {
					LevelMgr::instance()->destory_enemy(selected_enemy);
					selected_enemy = nullptr;
					if (DEBUG) SDL_Log("destory selected_enemy");
				}
				if (selected_item) {
					LevelMgr::instance()->destory_item(selected_item);
					selected_item = nullptr;
					if (DEBUG) SDL_Log("destory selected_item");
				}
				break;
			}
			}
			if (selected_enemy) {
				selected_enemy->set_pos(selected_enemy->get_pos() + move_axis);
			}
			if (selected_item) {
				selected_item->set_pos(selected_item->get_pos() + move_axis);
			}
		}
		else {
			switch (msg.key.keysym.sym) {
			case SDLK_UP:	window_pos.y -= 20;		break;
			case SDLK_DOWN: window_pos.y += 20;		break;
            case SDLK_LEFT: window_pos.x -= 20;		break;
            case SDLK_RIGHT:window_pos.x += 20;		break;

			case SDLK_RETURN: save();				break;
			}
		}
		break;
	}
	case SDL_MOUSEBUTTONDOWN:
	{
		if (msg.button.button == SDL_BUTTON_LEFT) {
			is_select = false;
			selected_enemy = nullptr;
            selected_item = nullptr;

			for (Enemy* enemy : LevelMgr::instance()->get_enemy_list()) {
				CollisionBox* box = enemy->get_block_box();
				if (mouse_in_box(box)) {
					selected_enemy = enemy;
					is_select = true;
					break;
				}
			}
			// 确保选中一个
			if (!is_select) {
				for (Item* item : LevelMgr::instance()->get_item_list()) {
					CollisionBox* box = item->get_block_box();
					if (mouse_in_box(box)) {
						selected_item = item;
						is_select = true;
						break;
					}
				}
			}
		}
		break;
	}

	}
}

void EditScene::on_exit() {
	LevelMgr::instance()->destory();
}

void EditScene::save() {
	std::ofstream file;
	file.open("resources\\level.txt", std::ios::out | std::ios::trunc);
	if (!file.is_open()) {
		SDL_Log("File Open ERROR");
		return;
	}

	for (Enemy* enemy : LevelMgr::instance()->get_enemy_list()) {
		file<<"enemy_list.push_back(new "<<enemy->get_name()<<"({ "<<enemy->get_pos().x<<","<<enemy->get_pos().y<<" }));"<<std::endl;
	}
	for (Item* item : LevelMgr::instance()->get_item_list()) {
		file << "item_list.push_back(new " << item->get_name() << "({ " << item->get_pos().x << "," << item->get_pos().y << " }));" << std::endl;
	}

	if (!file.good()) {
		SDL_Log("File Save ERROR");
		return;
	}
	file.close();
	if (DEBUG) {
        SDL_Log("File Save Success");
	}
}