#include "level_mgr.h"

LevelMgr::LevelMgr() = default;

LevelMgr::~LevelMgr() = default;

void LevelMgr::set_player(Player* player) {
	this->player = player;
}

void LevelMgr::destory() {
	delete player;

	for (auto& enemy : enemy_list) {
		delete enemy;
	}
	for (auto& item : item_list) {
		delete item;
	}
}

void LevelMgr::destory_enemy(Enemy* enemy) {
	auto it = std::find_if(enemy_list.begin(), enemy_list.end(),
		[enemy](Enemy* e) { return e == enemy; });
	if (it != enemy_list.end()) {
		delete* it;
		enemy_list.erase(it);
	}
}

void LevelMgr::destory_item(Item* item) {
	auto it = std::find_if(item_list.begin(), item_list.end(),
		[item](Item* i) { return i == item; });
	if (it != item_list.end()) {
		delete* it;
		item_list.erase(it);
	}
}

void LevelMgr::load_level(Level* level) {
	// É¾³ý new µÄ¶ÔÏó
	for (auto& enemy : enemy_list) {
		delete enemy;
	}
	for (auto& item : item_list) {
		delete item;
	}
	enemy_list.clear();
	item_list.clear();

	level->load();

	enemy_list = level->get_enemy_list();
	item_list = level->get_item_list();
}

Player* LevelMgr::get_player() {
	return player;
}

Enemy* LevelMgr::get_enemy(Enemy* enemy) {
	auto it = std::find(enemy_list.begin(), enemy_list.end(), enemy);
	return (it != enemy_list.end()) ? *it : nullptr;
}

Item* LevelMgr::get_item(Item* item) {
	auto it = std::find(item_list.begin(), item_list.end(), item);
	return (it != item_list.end()) ? *it : nullptr;
}

void LevelMgr::on_input(const SDL_Event& msg) {
	player->on_input(msg);
}

void LevelMgr::on_update(float delta) {
	player->on_update(delta);
	for (auto enemy : enemy_list) {
		enemy->on_update(delta);
	}
	//for (auto item : item_list) {
	//	item->on_update(delta);
	//}
}
void LevelMgr::on_render(Camera& camera) {
	player->on_render(camera);
	for (auto enemy : enemy_list) {
		enemy->on_render(camera);
	}
	//for (auto item : item_list) {
	//	item->on_render(camera);
	//}
}

