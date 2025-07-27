#pragma once
#include "level.h"

class Level1 : public Level {
	void load() override {
		//enemy_list.push_back(new Mushroom({ 100,200 }));
		//enemy_list.push_back(new Skeleton({ 300,200 }));

		item_list.push_back(new plant({ 0,680 }));
		item_list.push_back(new notebook({ 0,500 }));
		item_list.push_back(new BoxCat({ 400,600 }));
	}
};
