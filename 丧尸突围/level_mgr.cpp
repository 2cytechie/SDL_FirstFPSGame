#include "level_mgr.h"
#include "level1.h"
#include "player_ins.h"

LevelMgr::LevelMgr() = default;

LevelMgr::~LevelMgr() = default;

void LevelMgr::select_player(int select) {
	delete player;
	player = nullptr;
	switch (select) {
	case 0:		player = new Sprites();		break;
	case 1:		player = new Pexel();		break;
	case 2:		player = new Knight();		break;
	case 3:		player = new Soldier();		break;
	case 4:		player = new Fighter();		break;
	case 5:		player = new Samurai();		break;
	case 6:		player = new Martial();		break;

	default:	SDL_Log("Creat player Error !!!");
	}
}

void LevelMgr::destory() {
	delete current_level;
	current_level = nullptr;

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
	N_Level = n;
	timer_show_name.set_wait_time(3.0f);
	timer_show_name.set_one_shot(true);
	timer_show_name.set_on_timeout([&]() {
		show_level_name = false;
		});
	timer_show_name.restart();

	delete background;
	background = ResMgr::instance()->find_animation("background");

	// 删除 new 的对象
	destory();

	// 增加关卡  再次  load_level  创建下一关
	switch (N_Level++) {
	case 1: current_level = new Level1();	break;

	default:
		SDL_Log("N_level ERROR !!!");
	}

	current_level->load();
	level_name = current_level->get_name();
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
	timer_show_name.on_update(delta);

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
	if (show_level_name) {
		background->on_render(camera);
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

