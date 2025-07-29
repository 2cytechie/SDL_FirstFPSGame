#pragma once

#include "singleton.h"
#include "player.h"
#include "enemy.h"
#include "item.h"
#include "level.h"
#include <vector>

class LevelMgr : public Singleton<LevelMgr> {
	friend Singleton<LevelMgr>;
public:
	void select_player(int select);
	void destory_enemy(Enemy* enemy);
	void destory_item(Item* item);
	void destory();

	Player* get_player();

	// 编辑器模式
	void add_enemy(Enemy* enemy) {
		enemy_list.push_back(enemy);
	}
	void add_item(Item* item) {
        item_list.push_back(item);
	}
	std::vector<Enemy*> get_enemy_list() {
		return enemy_list;
	}
	std::vector<Item*> get_item_list() {
		return item_list;
	}

	void load_level(int n);
	
	void on_input(const SDL_Event& msg);
	void on_update(float delta);
	void on_render(Camera & camera);

private:
	LevelMgr();

	~LevelMgr();

	int N_Level = 1;							// 第 N_Level 关卡
	Timer timer_show_name;
	Animation* background = nullptr;
	bool show_level_name = false;
	Text* level_name = nullptr;					// 关卡名字

	Player* player = nullptr;
	std::vector<Enemy*> enemy_list;
	std::vector<Item*> item_list;

	Level* current_level = nullptr;				// 当前关卡

};
