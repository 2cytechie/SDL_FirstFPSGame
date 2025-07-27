#include "level_mgr.h"
#include "level1.h"

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

	player = nullptr;
	enemy_list.clear();
	item_list.clear();
}

void LevelMgr::destory_enemy(Enemy* enemy) {
	if(!enemy) return;

	auto it = std::find_if(enemy_list.begin(), enemy_list.end(),
		[enemy](Enemy* e) { return e == enemy; });
	if (it != enemy_list.end()) {
		delete* it;
		enemy_list.erase(it);
	}
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
	// 删除 new 的对象
	for (auto& enemy : enemy_list) {
		delete enemy;
	}
	for (auto& item : item_list) {
		delete item;
	}
	enemy_list.clear();
	item_list.clear();

	// 增加关卡
	switch (n) {
	case 1: current_level = new Level1();	break;

	default:
		SDL_Log("N_level ERROR !!!");
	}

	current_level->load();
	enemy_list = current_level->get_enemy_list();
	item_list = current_level->get_item_list();
}

Player* LevelMgr::get_player() {
	return player;
}

void LevelMgr::on_input(const SDL_Event& msg) {
	if (!player) return;
	player->on_input(msg);
}

void LevelMgr::on_update(float delta) {
	for (auto item : item_list) {
		item->on_update(delta);
	}
	for (auto enemy : enemy_list) {
		enemy->on_update(delta);
	}
	if (!player) return;
	player->on_update(delta);
}
void LevelMgr::on_render(Camera& camera) {
	for (auto item : item_list) {
		item->on_render(camera);
	}
	for (auto enemy : enemy_list) {
		enemy->on_render(camera);
	}
	if (!player) return;
	player->on_render(camera);
}

