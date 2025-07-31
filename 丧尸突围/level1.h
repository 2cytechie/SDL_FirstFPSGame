#pragma once
#include "level.h"

class Level1 : public Level {
	void load() override {
		font = TTF_OpenFont("resources/IPix.ttf", 100);
		name = new Text(u8"Óà½ý·ÐÑª", font, { 1280 / 2,720 / 2 });

		//enemy_list.push_back(new Mushroom({ 100,200 }));
		//enemy_list.push_back(new Skeleton({ 300,200 }));

		item_list.push_back(new plant({ 0,680 }));
		item_list.push_back(new notebook({ 0,500 }));
		item_list.push_back(new BoxCat({ 400,600 }));
	}

	void death_buff() {
		// Ôö¼ÓÑªÁ¿
		for (Enemy* enemy : enemy_list) {
			enemy->plus_max_hp(10);
		}
	}
};
