#include "edit_scene.h"
#include "level_mgr.h"
#include "scene_mgr.h"
#include "player_ins.h"
#include "enemy_ins.h"
#include "item_ins.h"

extern bool DEBUG;

bool EditScene::mouse_in_box(CollisionBox* box) {
	Vector2 box_pos = box->get_pos() - window_pos;
	Vector2 box_size = box->get_size();
    return mouse_pos.x >= box_pos.x - box_size.x / 2 && mouse_pos.x <= box_pos.x + box_size.x / 2 &&
        mouse_pos.y >= box_pos.y - box_size.y / 2 && mouse_pos.y <= box_pos.y + box_size.y / 2;
}

void EditScene::on_enter() {
	// 设置编辑关卡
	LevelMgr::instance()->load_level(EDIT_LEVEL);
	// 默认角色  并不设置重力
	LevelMgr::instance()->select_player(1);
	LevelMgr::instance()->get_player()->set_gravity_enabled(false);
}

void EditScene::on_update(float delta) {
	// 敌人和角色状态机都不能更新  需要手动关闭  让状态机保持 Idle 状态
	// enemy_state_node.cpp -> EnemyIdleState::on_update
	// player_state_node.cpp -> PlayerIdleState::on_update
	LevelMgr::instance()->on_update(delta);
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
	if (msg.type == SDL_KEYDOWN) {
		std::string item_name;
        switch (msg.key.keysym.sym) {
		case SDLK_1:	LevelMgr::instance()->add_item(new grass_plant(window_pos + mouse_pos));						break;
        case SDLK_2:	LevelMgr::instance()->add_item(new grass_plant2(window_pos + mouse_pos));							break;
        case SDLK_3:	LevelMgr::instance()->add_item(new plant(window_pos + mouse_pos));						break;
		case SDLK_4:	LevelMgr::instance()->add_item(new plant2(window_pos + mouse_pos));				break;
		case SDLK_5:	item_name = "cherry_tree";				break;
		case SDLK_6:	item_name = "background_cloud3";				break;
		case SDLK_7:	item_name = "background_layer";					break;
		case SDLK_8:	LevelMgr::instance()->add_item(new stream(window_pos + mouse_pos));			break;
		case SDLK_9:	LevelMgr::instance()->add_item(new waterfall(window_pos + mouse_pos));				break;
		case SDLK_a:	item_name = "tree1";			break;
		case SDLK_b:	item_name = "YellowCat";				break;
		case SDLK_c:	item_name = "stump";			break;
		case SDLK_d:	item_name = "taboret";			break;
		case SDLK_e:	item_name = "streelight";				break;
		case SDLK_f:	item_name = "trunk";			break;
		case SDLK_g:	item_name = "background1";						break;
		case SDLK_h:	item_name = "background2";						break;
		case SDLK_i:	item_name = "BoxCat";							break;
		case SDLK_j:	LevelMgr::instance()->add_item(new bridge_left(window_pos + mouse_pos));						break;
		case SDLK_k:	LevelMgr::instance()->add_item(new bridge_mid(window_pos + mouse_pos));						break;
        case SDLK_l:	LevelMgr::instance()->add_item(new bridge_right(window_pos + mouse_pos));						break;
        case SDLK_m:	item_name = "bush1";							break;
        case SDLK_n:	item_name = "bush2";							break;
        case SDLK_o:	item_name = "flower_blue";						break;
        case SDLK_p:	item_name = "lemongrass";						break;
        case SDLK_q:	item_name = "lemongrasses";						break;
        case SDLK_r:	item_name = "lotus";							break;
        case SDLK_s:	item_name = "mushroom1";						break;
        case SDLK_t:	item_name = "mushroom2";						break;
        case SDLK_u:	item_name = "mushroom3";						break;
        case SDLK_v:	item_name = "mushroom4";						break;
        case SDLK_w:	item_name = "mushroom5";						break;
        case SDLK_x:	item_name = "red_spider_lily";							break;
        case SDLK_y:	item_name = "rock_1";							break;
        case SDLK_z:	item_name = "next_level_right";						break;
			
		}
		if (!item_name.empty()) {
			LevelMgr::instance()->add_item(new Item(item_name, window_pos + mouse_pos));
		}

		std::string enemy_name;
		switch (msg.key.keysym.sym) {
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
		if (!enemy_name.empty()) {
			LevelMgr::instance()->add_enemy(new Enemy(enemy_name, window_pos + mouse_pos));
		}

		// 敌人不启用重力
		if (!LevelMgr::instance()->get_enemy_list().empty()) {
			Enemy* enemy = LevelMgr::instance()->get_enemy_list().back();
			if (enemy) {
				enemy->set_gravity_enabled(false);
			}
		}

	}

	switch (msg.type) {
	case SDL_KEYDOWN: 
	{
		Vector2 move_axis;
		switch (msg.key.keysym.sym) {
		case SDLK_UP:	move_axis.y -= 1;		break;
		case SDLK_DOWN: move_axis.y += 1;		break;
		case SDLK_LEFT: move_axis.x -= 1;		break;
		case SDLK_RIGHT:move_axis.x += 1;		break;
		case SDLK_RETURN: save();				break;

		case SDLK_BACKSPACE:
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
		case SDLK_EQUALS:
			if (selected_enemy) {
				selected_enemy->plus_magnification(0.1);
			}
			if (selected_item) {
				selected_item->plus_magnification(0.1);
			}
			break;
		case SDLK_MINUS:
			if (selected_enemy) {
				selected_enemy->minus_magnification(0.1);
			}
			if (selected_item) {
				selected_item->minus_magnification(0.1);
			}
			break;
		}
		if (selected_enemy) {
			selected_enemy->set_pos(selected_enemy->get_pos() + move_axis);
		}
		if (selected_item) {
			selected_item->set_pos(selected_item->get_pos() + move_axis);
		}
		break;
	}
	case SDL_MOUSEBUTTONDOWN:
		if (msg.button.button == SDL_BUTTON_LEFT) {
			is_left_button_down = true;
			selected_enemy = nullptr;
			selected_item = nullptr;

			bool is_selected = false;
			for (Enemy* enemy : LevelMgr::instance()->get_enemy_list()) {
				CollisionBox* box = enemy->get_block_box();
				if (mouse_in_box(box)) {
					selected_enemy = enemy;
					is_selected = true;
					if (DEBUG) SDL_Log("Selected Enemy");
					break;
				}
			}
			// 确保选中一个
			if (!is_selected) {
				for (Item* item : LevelMgr::instance()->get_item_list()) {
					CollisionBox* box = item->get_block_box();
					if (mouse_in_box(box)) {
						selected_item = item;
						if (DEBUG) SDL_Log("Selected Item");
						break;
					}
				}
			}
		}
        if (msg.button.button == SDL_BUTTON_RIGHT) {
			is_right_button_down = true;
		}
		break;
	case SDL_MOUSEBUTTONUP:
		is_left_button_down = false;
		is_right_button_down = false;
		break;
	case SDL_MOUSEMOTION:
		mouse_pos = Vector2(msg.motion.x, msg.motion.y);
		Vector2 mouse_motion = Vector2(msg.motion.xrel, msg.motion.yrel);
		if (is_left_button_down) {
			if (selected_enemy) {
				selected_enemy->set_pos(selected_enemy->get_pos() + mouse_motion);
			}
			if (selected_item) {
				selected_item->set_pos(selected_item->get_pos() + mouse_motion);
			}
		}
		// 移动窗口
        if (is_right_button_down) {
            window_pos -= mouse_motion;
        }
		break;
	}
}

void EditScene::on_exit() {
	LevelMgr::instance()->destory();
}

void EditScene::save() {
	nlohmann::json json;
	json["enemy"] = nlohmann::json::object();
	json["item"] = nlohmann::json::object();

	for (Enemy* enemy : LevelMgr::instance()->get_enemy_list()) {
		if (!enemy) continue;  // 避免空指针

		nlohmann::json enemy_json = enemy->to_json();
		std::string enemy_name = enemy_json["name"];
		auto& enemy_entry = json["enemy"][enemy_name];

		// 初始化需要push_back的数组
		if (!enemy_entry["pos_revive"].is_array()) {
			enemy_entry["pos_revive"] = nlohmann::json::array();
		}
		if (!enemy_entry["animation_magnification"].is_array()) {
			enemy_entry["animation_magnification"] = nlohmann::json::array();
		}

		enemy_entry["pos_revive"].push_back(enemy_json["pos_revive"]);
		enemy_entry["animation_magnification"].push_back(enemy_json["animation_magnification"]);

		// 仅首次设置
		if (enemy_entry["hit_box_size"].is_null()) {
			enemy_entry["hit_box_size"] = enemy_json["hit_box_size"];
		}
		if (enemy_entry["hurt_box_size"].is_null()) {
			enemy_entry["hurt_box_size"] = enemy_json["hurt_box_size"];
		}
		if (enemy_entry["max_hp"].is_null()) {
			enemy_entry["max_hp"] = enemy_json["max_hp"];
		}
		if (enemy_entry["animation_frame_delta"].is_null()) {
			enemy_entry["animation_frame_delta"] = enemy_json["animation_frame_delta"];
		}
		if (enemy_entry["attack"].is_null()) {
			enemy_entry["attack"] = enemy_json["attack"];
		}
	}

	for (Item* item : LevelMgr::instance()->get_item_list()) {
		if (!item) continue;  // 避免空指针

		nlohmann::json item_json = item->to_json();
		std::string item_name = item_json["name"];
		auto& item_entry = json["item"][item_name];

		// 初始化数组
		if (!item_entry["pos"].is_array()) {
			item_entry["pos"] = nlohmann::json::array();
		}
		if (!item_entry["animation_magnification"].is_array()) {
			item_entry["animation_magnification"] = nlohmann::json::array();
		}

		item_entry["pos"].push_back(item_json["pos"]);
		item_entry["animation_magnification"].push_back(item_json["animation_magnification"]);

		// 非数组字段首次设置
		if (item_entry["is_block"].is_null()) {
			item_entry["is_block"] = item_json["is_block"];
		}
		if (item_entry["block_box_size"].is_null()) {
            item_entry["block_box_size"] = item_json["block_box_size"];
		}
		if (item_entry["animation_frame_delta"].is_null()) {
			item_entry["animation_frame_delta"] = item_json["animation_frame_delta"];
		}
	}

	std::ofstream out("resources\\level.json");
	if (out.is_open()) {
		out << json;
		out.close();
		SDL_Log("File Save Success To resources\\level.json");
	}
	else {
		SDL_Log("File Open ERROR");
		return;
	}
}
