#pragma once

#include "player.h"

class Sprites :public Player {
public:
	Sprites() {
		name = "Sprites";
		hp = 100;
		max_hp = 100;
		pos = Vector2(100, 100);
		logic_height = 120;

		animation_magnification = 3.0f;
		animation_frame_delta = 0.1f;

		hit_box->set_size({ 100,120 });
		hurt_box->set_size({ 60,100 });
	}

	~Sprites() = default;

};
