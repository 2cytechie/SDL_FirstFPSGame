#pragma once
#include "level.h"

class Level1 : public Level {
	void load() override {
		std::string level_name = u8"Óà½ý·ÐÑª";
		std::string level_config_path = "level1.json";

		font = TTF_OpenFont("resources/IPix.ttf", 100);
		name = new Text(level_name, font, { 1280 / 2,720 / 2 });

		std::ifstream f(level_config_path);
		nlohmann::json data = nlohmann::json::parse(f);

		for (auto& enemy : data["enemy"]) {
			enemy_list.push_back(new Enemy(enemy));
		}
		for (auto& item : data["item"]) {
            item_list.push_back(new Item(item));
		}
	}

	void death_buff() {
		// Ôö¼ÓÑªÁ¿
		for (Enemy* enemy : enemy_list) {
			enemy->plus_max_hp(10);
		}
	}
};
