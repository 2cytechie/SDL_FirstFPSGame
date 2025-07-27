#pragma once

#include "vector2.h"
#include "animation.h"
#include "collision_mgr.h"

class Item {
public:
	Item(Vector2 p);

	~Item();

	void init();
	void on_update(float delta);
	void on_render(Camera& camera);

protected:
	std::string name;
	Vector2 pos;
	float animation_magnification = 1;				// �Ŵ���
	float animation_frame_delta = 0.1f;				// ����ÿ֡ʱ��
	bool is_facing_right = true;
	CollisionBox* block_box = nullptr;
	Animation* animation = nullptr;
};
