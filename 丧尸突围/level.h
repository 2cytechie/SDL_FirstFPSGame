#pragma once

#include <vector>

#include "enemy_ins.h"
#include "item_ins.h"

class Level {
public:
	virtual void load() = 0;

	std::vector<Enemy*> get_enemy_list() {
		return enemy_list;
	}
	std::vector<Item*> get_item_list() {
		return item_list;
	}

protected:
	std::string name;
	std::vector<Enemy*> enemy_list;
	std::vector<Item*> item_list;

};
