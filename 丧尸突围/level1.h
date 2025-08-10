#pragma once
#include "level.h"

class Level1 : public Level {
    void load() override {
        level_name = u8"Óà½ý·ÐÑª";
        level_config_path = "resources\\level.json";

        Level::load();
    }


	void death_buff() override {
		// Ôö¼ÓÑªÁ¿
		if (DEBUG) {
			SDL_Log("Enemy plus HP");
		}
		for (Enemy* enemy : enemy_list) {
			//enemy->plus_max_hp(10);
		}
	}
};
