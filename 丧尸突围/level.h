#pragma once

#include <vector>
#include <fstream>
#include "scene_mgr.h"
#include "enemy.h"
#include "item.h"

class Level {
public:
	Level() = default;

	~Level() {
		TTF_CloseFont(font);
		delete name;
	}
	Text* get_name() {
		return name;
	}
	std::vector<Enemy*> get_enemy_list() {
		return enemy_list;
	}
	std::vector<Item*> get_item_list() {
		return item_list;
	}

    virtual void death_buff() = 0;
	virtual void load() {
        font = TTF_OpenFont("resources/IPix.ttf", 100);
        name = new Text(level_name, font, { 1280 / 2, 720 / 2 });

        std::ifstream f(level_config_path);
        if (!f.is_open()) {
            SDL_Log("Failed to open level config file: %s", level_config_path.c_str());
            return;
        }

        nlohmann::json data;
        try {
            data = nlohmann::json::parse(f);
        }
        catch (const nlohmann::json::parse_error& e) {
            SDL_Log("JSON parse error: %s", e.what());
            return;
        }

        for (auto& [enemy_name, enemy_group] : data["enemy"].items()) {
            for (int i = 0; i < enemy_group["pos_revive"].size(); i++) {
                nlohmann::json enemy_piece;

                enemy_piece["name"] = enemy_name;
                enemy_piece["pos_revive"] = enemy_group["pos_revive"][i];
                enemy_piece["hit_box_size"] = enemy_group["hit_box_size"];
                enemy_piece["hurt_box_size"] = enemy_group["hurt_box_size"];
                enemy_piece["max_hp"] = enemy_group["max_hp"];
                enemy_piece["animation_magnification"] = enemy_group["animation_magnification"][i];
                enemy_piece["animation_frame_delta"] = enemy_group["animation_frame_delta"];
                enemy_piece["attack"] = enemy_group["attack"];
                if (enemy_group.contains("enable_gravity")) {
                    enemy_piece["enable_gravity"] = enemy_group["enable_gravity"];
                }

                Enemy* enemy = new Enemy(enemy_piece);
                // 编辑模式下不设置重力
                //enemy->set_gravity_enabled(false);

                enemy_list.push_back(enemy);
            }
        }
        for (auto& [item_name, item_group] : data["item"].items()) {
            for (int i = 0; i < item_group["pos"].size(); i++) {
                nlohmann::json item_piece;

                item_piece["name"] = item_name;
                item_piece["pos"] = item_group["pos"][i];
                item_piece["is_block"] = item_group["is_block"];
                item_piece["block_box_size"] = item_group["block_box_size"];
                item_piece["animation_magnification"] = item_group["animation_magnification"][i];
                item_piece["animation_frame_delta"] = item_group["animation_frame_delta"];
                item_piece["relative_camera_speed"] = item_group["relative_camera_speed"];

                item_list.push_back(new Item(item_piece));
            }
        }
	}

protected:
    std::string level_name;
    std::string level_config_path;
	TTF_Font* font = nullptr;
	Text* name = nullptr;
	std::vector<Enemy*> enemy_list;
	std::vector<Item*> item_list;

};
