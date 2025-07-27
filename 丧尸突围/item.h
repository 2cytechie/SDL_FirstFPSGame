#pragma once

#include "vector2.h"
#include "animation.h"
#include "collision_mgr.h"

class Item {
public:
	Item(Vector2 p);

	~Item();

	CollisionBox* get_block_box() {
		return block_box;
	}

	void set_pos(Vector2 p) {
		pos = p;
	}

	Vector2 get_pos() {
		return pos;
	}

	std::string get_name() {
		return name;
	}

	void init();
	void on_update(float delta);
	void on_render(Camera& camera);

protected:
	std::string name;
	Vector2 pos;									// 位置
	float animation_magnification = 1;				// 放大倍数
	float animation_frame_delta = 0.1f;				// 动画每帧时间
	bool is_facing_right = true;
	CollisionBox* block_box = nullptr;
	Animation* animation = nullptr;
};
