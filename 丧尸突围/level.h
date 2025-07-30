#pragma once

#include <vector>

#include "enemy_ins.h"
#include "item_ins.h"

class Level {
public:
	Level() = default;

	~Level() {
		TTF_CloseFont(font);
		delete name;
		for (auto enemy : enemy_list) {
			delete enemy;
		}
		for (auto item : item_list) {
			delete item;
		}
	}

	virtual void load() = 0;
	virtual void enemy_strung() = 0;

	Text* get_name() {
		return name;
	}
	std::vector<Enemy*> get_enemy_list() {
		return enemy_list;
	}
	std::vector<Item*> get_item_list() {
		return item_list;
	}

protected:
	TTF_Font* font = nullptr;
	Text* name = nullptr;
	std::vector<Enemy*> enemy_list;
	std::vector<Item*> item_list;

};
