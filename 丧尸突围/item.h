#pragma once
#include "vector2.h"
#include "animation.h"
#include "collision_mgr.h"
#include <json.hpp>

class Item {
public:
	Item(Vector2 p);
	Item(std::string name, Vector2 p);
	Item(nlohmann::json& json);

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

	void plus_magnification(float val) {
		animation_magnification += val;
		animation->set_size(animation_magnification);
		block_box->set_size(animation->get_size());
	}

	void minus_magnification(float val) {
		animation_magnification -= val;
		animation->set_size(animation_magnification);
		block_box->set_size(animation->get_size());
	}

	nlohmann::json to_json() const;

	void init();
	void on_update(float delta);
	void on_render(Camera& camera);

protected:
	std::string name;
	Vector2 pos;									// λ��
	float relative_camera_speed = 0.0f;				// �����������ƶ��ٶ�
	float animation_magnification = 1;				// �Ŵ���
	float animation_frame_delta = 0.1f;				// ����ÿ֡ʱ��
	bool is_facing_right = true;
	bool is_block = false;							// �Ƿ�����ײ
	CollisionBox* block_box = nullptr;
	Animation* animation = nullptr;
};
