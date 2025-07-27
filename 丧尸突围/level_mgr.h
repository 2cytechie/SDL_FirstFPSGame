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
	void set_player(Player* player);
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

	Timer timer_show_name;
	std::string level_name;						// 关卡名字
	int N_level = 1;							// 第 几 关

	Player* player = nullptr;
	std::vector<Enemy*> enemy_list;
	std::vector<Item*> item_list;

	Level* current_level = nullptr;				// 当前关卡

};
