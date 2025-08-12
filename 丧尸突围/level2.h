#pragma once
#include "level.h"

class Level2 : public Level {
	void load() override {
		level_name = u8"余影渐拓";
		level_config_path = "resources\\level\\level2.json";

		Level::load();
	}


	void death_buff() override {
		// 增加攻击力
		if (DEBUG) {
			SDL_Log("Enemy plus attack");
		}
		for (Enemy* enemy : enemy_list) {
			enemy->plus_attack(2);
			enemy->plus_max_hp(2);
		}
	}
};
