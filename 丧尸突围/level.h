#pragma once

#include <vector>

#include "player.h"
#include "enemy.h"
#include "item.h"

class Level {
public:
	void set_plyer(Player* player) {
		this->player = player;
	}

	void add_enemy(Enemy* enemy) {
		enemy_list.push_back(enemy);
	}

	void add_item(Item* item) {
		item_list.push_back(item);
	}

	Player* get_player() {
		return player;
	}

	std::vector<Enemy*> get_enemy_list() {
		return enemy_list;
	}

	std::vector<Item*> get_item_list() {
		return item_list;
	}

private:
	Player* player = nullptr;
	std::vector<Enemy*> enemy_list;
	std::vector<Item*> item_list;

};
