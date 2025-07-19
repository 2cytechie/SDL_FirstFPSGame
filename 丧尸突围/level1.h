#pragma once
#include "level.h"

class Level1 : public Level {
	void load() override {
		enemy_list.push_back(new Mushroom({ 100,200 }));
		enemy_list.push_back(new Skeleton({ 300,200 }));
	}
};
