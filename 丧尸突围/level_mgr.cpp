#include "level_mgr.h"
#include "level1.h"
#include "level2.h"
#include "player_ins.h"

LevelMgr::LevelMgr() = default;

LevelMgr::~LevelMgr() = default;

void LevelMgr::select_player(int select) {
	if (player) {
		delete player;
		player = nullptr;
	}
	switch (select) {
	case 0:		player = new Sprites();		break;
	case 1:		player = new Pexel();		break;
	case 2:		player = new Soldier();		break;
	case 3:		player = new Fighter();		break;
	case 4:		player = new Samurai();		break;
	case 5:		player = new Martial();		break;

	default:	SDL_Log("Creat player Error !!!");
	}
}

void LevelMgr::destory() {
	delete current_level;
	current_level = nullptr;

	for (auto& enemy : enemy_list) {
		delete enemy;
	}
	for (auto& item : item_list) {
		delete item;
	}

	enemy_list.clear();
	item_list.clear();
}

void LevelMgr::destory_enemy(Enemy* enemy) {
	if (DEBUG) {
		SDL_Log("destory enemy : %s",enemy->get_name().c_str());
	}

	if(!enemy) return;

	auto it = std::find_if(enemy_list.begin(), enemy_list.end(),
		[enemy](Enemy* e) { return e == enemy; });
	if (it != enemy_list.end()) {
		delete* it;
		enemy_list.erase(it);
	}

	// 死亡触发关卡事件
	current_level->death_buff();
}

void LevelMgr::destory_item(Item* item) {
	if (!item) return;

	auto it = std::find_if(item_list.begin(), item_list.end(),
		[item](Item* i) { return i == item; });

	if (it != item_list.end()) {
		delete* it;
		item_list.erase(it);
	}
}

void LevelMgr::load_level(int n) {
	timer_show_name.set_wait_time(1.5f);
	timer_show_name.set_one_shot(true);
	timer_show_name.set_on_timeout([&]() {
		show_level_name = false;
		});
	timer_show_name.restart();

	if (!background) {
		background = ResMgr::instance()->find_animation("background");
	}

	// 删除 new 的对象
	destory();

	switch (n) {
	case 1: current_level = new Level1();	break;
	case 2: current_level = new Level2();	break;

	default:
		SDL_Log("level_num ERROR !!!");
	}

	current_level->load();
	level_name = current_level->get_name();
	enemy_list = current_level->get_enemy_list();
	item_list = current_level->get_item_list();

	// 玩家增加血量和攻击力
	if (player) {
		player->reset();
		player->plus_max_hp(25);
		player->plus_attack(5);

		if (DEBUG) {
			SDL_Log("player plus max_hp and attack");
		}
	}
}

Player* LevelMgr::get_player() {
	return player;
}

void LevelMgr::on_input(const SDL_Event& msg) {
	if (!player) return;
	player->on_input(msg);
}

void LevelMgr::on_update(float delta) {
	timer_show_name.on_update(delta);

	for (auto item : item_list) {
		item->on_update(delta);
		if (item->get_name().substr(0, 10) == "next_level") {
			if (!player) return;
			Vector2 dis = player->get_pos() - item->get_pos();
			if (dis.length() < 500 && dis.x < 10) {
				is_win = true;
				show_level_name = true;
				break;
			}
		}
	}
	for (auto enemy : enemy_list) {
		enemy->on_update(delta);
	}
	if (!player) return;
	player->on_update(delta);
}
void LevelMgr::on_render(Camera& camera) {
	// 设置摄像机跟随
	if (player) {
		Vector2 player_pos = player->get_pos();
		bool is_facing_right = player->facing_right();
		camera.follow_pos(player_pos, is_facing_right);
	}
	if (show_level_name) {
		camera.reset();
		if (background) {
			background->on_render(camera);
		}
		camera.draw_text(level_name);
	}
	else {
		for (auto item : item_list) {
			item->on_render(camera);
		}
		for (auto enemy : enemy_list) {
			enemy->on_render(camera);
		}
		if (!player) return;
		player->on_render(camera);
	}
}

