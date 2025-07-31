#include "edit_scene.h"
#include "level_mgr.h"
#include "scene_mgr.h"
#include "player_ins.h"
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
	// ���ñ༭�ؿ�
	LevelMgr::instance()->load_level(EDIT_LEVEL);
	// Ĭ�Ͻ�ɫ  ������������
	LevelMgr::instance()->select_player(1);
	LevelMgr::instance()->get_player()->set_gravity_enabled(false);
}

void EditScene::on_update(float delta) {
	// ���˺ͽ�ɫ״̬�������ܸ���  ��Ҫ�ֶ��ر�  ��״̬������ Idle ״̬
	// enemy_state_node.cpp -> EnemyIdleState::on_update
	// player_state_node.cpp -> PlayerIdleState::on_update
	LevelMgr::instance()->on_update(delta);
}

void EditScene::on_render(Camera& camera) {
	camera.set_pos(window_pos);

	// ����
	SDL_Color bg_color{ 0,255,255,255 };
	SDL_Rect rect{
		0,0,
		1280,720
	};
	camera.fill_rect(&rect, bg_color);

	LevelMgr::instance()->on_render(camera);

	// DEBUG ��ײ��
	CollisionMgr::instance()->on_debug_render(camera);
}

void EditScene::on_input(const SDL_Event& msg) {
	/*
	���̴� 1 ��ʼΪItem
	С���̴� 0 ��ʼΪEnemy
	������ѡ����Ʒ
	ENTER �����ļ����㴴���ؿ�
	BACK ɾ����Ʒ
	*/
	if (msg.type == SDL_KEYDOWN) {
		std::string item_name;
        switch (msg.key.keysym.sym) {
		case SDLK_1:	item_name = "grass_plant";						break;
        case SDLK_2:	item_name = "plant";							break;
        case SDLK_3:	item_name = "background";						break;
		case SDLK_4:	item_name = "background_cloud1";				break;
		case SDLK_5:	item_name = "background_cloud2";				break;
		case SDLK_6:	item_name = "background_cloud3";				break;
		case SDLK_7:	item_name = "background_layer";					break;
		case SDLK_8:	item_name = "background_mountion1";				break;
		case SDLK_9:	item_name = "background_mountion2";				break;
		case SDLK_a:	item_name = "background_tree1_left";			break;
		case SDLK_b:	item_name = "background_tree1_mid";				break;
		case SDLK_c:	item_name = "background_tree1_righ";			break;
		case SDLK_d:	item_name = "background_tree2_left";			break;
		case SDLK_e:	item_name = "background_tree2_mid";				break;
		case SDLK_f:	item_name = "background_tree2_right";			break;
		case SDLK_g:	item_name = "background1";						break;
		case SDLK_h:	item_name = "background2";						break;
		case SDLK_i:	item_name = "BoxCat";							break;
		case SDLK_j:	item_name = "bridge_left";						break;
		case SDLK_k:	item_name = "bridge_mid";						break;
        case SDLK_l:	item_name = "bridge_right";						break;
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
        case SDLK_x:	item_name = "notebook";							break;
        case SDLK_y:	item_name = "rock_1";							break;
        case SDLK_z:	item_name = "next_level";						break;
			
		}
		if (!item_name.empty()) {
			LevelMgr::instance()->add_item(new Item(item_name, window_pos + mouse_pos));
		}

		std::string enemy_name;
		switch (msg.key.keysym.sym) {
		case SDLK_KP_0:	enemy_name = "FlyingEye";			break;
		case SDLK_KP_1:	enemy_name = "Goblin";				break;
		case SDLK_KP_2:	enemy_name = "Mushroom";			break;
		case SDLK_KP_3:	enemy_name = "Skeleton";			break;
		case SDLK_KP_4:	enemy_name = "SpriteSheets";		break;
		case SDLK_KP_5:	enemy_name = "Ninja";				break;
		case SDLK_KP_6:	enemy_name = "Minotaur";			break;
		case SDLK_KP_7:	enemy_name = "Slime1";				break;
		case SDLK_KP_8:	enemy_name = "Slime2";				break;

		}
		if (!enemy_name.empty()) {
			LevelMgr::instance()->add_enemy(new Enemy(enemy_name, window_pos + mouse_pos));
		}

		// ���˲���������
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
		case SDLK_UP:	move_axis.y -= 10;		break;
		case SDLK_DOWN: move_axis.y += 10;		break;
		case SDLK_LEFT: move_axis.x -= 10;		break;
		case SDLK_RIGHT:move_axis.x += 10;		break;
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
			// ȷ��ѡ��һ��
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
		// �ƶ�����
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

	int count = 0;
	for (Enemy* enemy : LevelMgr::instance()->get_enemy_list()) {
		count++;

		nlohmann::json enemy_json = enemy->to_json();
		auto& enemy_name = enemy_json["name"];
		auto& enemy_entry = json["enemy"][enemy_name];

		enemy_entry["count"] = count;
		enemy_entry["pos_revive"].push_back(enemy_json["pos_revive"]);
		enemy_entry["hit_box_size"] = enemy_json["hit_box_size"];
		enemy_entry["hurt_box_size"] = enemy_json["hurt_box_size"];
		enemy_entry["max_hp"] = enemy_json["max_hp"];
		enemy_entry["animation_magnification"] = enemy_json["animation_magnification"];
		enemy_entry["animation_frame_delta"] = enemy_json["animation_frame_delta"];
		enemy_entry["attack"] = enemy_json["attack"];
	}

	count = 0;
	for (Item* item : LevelMgr::instance()->get_item_list()) {
		count++;

		nlohmann::json enemy_json = item->to_json();
		auto& enemy_name = enemy_json["name"];
		auto& enemy_entry = json["item"][enemy_name];

		enemy_entry["count"] = count;
		enemy_entry["pos"].push_back(enemy_json["pos"]);
		enemy_entry["is_block"] = enemy_json["is_block"];
		enemy_entry["animation_magnification"] = enemy_json["animation_magnification"];
		enemy_entry["animation_frame_delta"] = enemy_json["animation_frame_delta"];
	}


	std::ofstream out("resources\\level.json");
	if (out.is_open()) {
		out << json;
		out.close();
		SDL_Log("File Save Success");
	}
	else {
		SDL_Log("File Open ERROR");
		return;
	}
}