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
	void destory();
	void destory_enemy(Enemy* enemy);
	void destory_item(Item* item);

	Player* get_player();
	Enemy* get_enemy(Enemy* enemy);
	Item* get_item(Item* item);

	void load_level(Level* level);

	void on_input(const SDL_Event& msg);
	void on_update(float delta);
	void on_render(Camera & camera);

private:
	LevelMgr();

	~LevelMgr();

	std::string level_name;						// 关卡名字
	int current_level = 1;						// 第 几 关

	Player* player = nullptr;
	std::vector<Enemy*> enemy_list;
	std::vector<Item*> item_list;

};
