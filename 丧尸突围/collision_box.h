#pragma once

#include "vector2.h"
#include "collision_layer.h"

#include<functional>

class CollisionMgr;

class CollisionBox {
	friend class CollisionMgr;

private:
	Vector2 size;				// �ߴ�
	Vector2 pos;				// ���ĵ�λ��
	bool enabled = true;		// �Ƿ������ײ���
	std::function<void(const CollisionBox* box)> on_collide;
	CollisionLayer layer_src = CollisionLayer::None;
	CollisionLayer layer_dst = CollisionLayer::None;

private:
	CollisionBox() = default;
	~CollisionBox() = default;

public:
	void set_enabled(bool flag) {
		enabled = flag;
	}

	void set_layer_src(CollisionLayer layer) {
		layer_src = layer;
	}

	void set_layer_dst(CollisionLayer layer) {
		layer_dst = layer;
	}

	void set_on_collide(std::function<void(const CollisionBox* box)> on_collide) {
		this->on_collide = on_collide;
	}

	void set_size(const Vector2& size) {
		this->size = size;
	}

	void set_pos(const Vector2& pos) {
		this->pos = pos;
	}

	const Vector2& get_size() const {
		return size;
	}

	const Vector2& get_pos()const {
		return pos;
	}

};