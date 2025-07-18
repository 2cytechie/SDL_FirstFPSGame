#pragma once

#include "vector2.h"
#include "timer.h"
#include "animation.h"
#include "state_machine.h"
#include "collision_mgr.h"

class Character {
public:
	Character();
	~Character();

	std::string get_name() {
		return name;
	}

	void decrease_hp(int damage);

	int get_hp() {
		return hp;
	}

	void set_pos(const Vector2& pos) {
		this->pos = pos;
	}

	const Vector2& get_pos() {
		return pos;
	}

	void set_velocity(const Vector2& velocity) {
		this->velocity = velocity;
	}

	const Vector2& get_velocity() {
		return velocity;
	}

	float get_logic()const {
		return logic_height;
	}

	bool facing_right() {
		return is_facing_right;
	}

	void set_gravity_enabled(bool flag) {
		enable_gravity = flag;
	}

	CollisionBox* get_hit_box() {
		return hit_box;
	}

	CollisionBox* get_hurt_box() {
		return hurt_box;
	}

	bool is_on_floor()const {
		return pos.y >= FLOOR_Y;
	}

	float get_floor_y()const {
		return FLOOR_Y;
	}

	void make_invulnerable() {
		is_invulnerable = true;
		timer_invulnerable_status.restart();
	}

	virtual void on_input(const SDL_Event& msg);
	virtual void on_update(float delta);
	virtual void on_render(Camera& camera);

	virtual void on_hurt();

	void set_animation(const std::string& id);


protected:
	const float FLOOR_Y = 620;										// �ذ���ֱ��������
	const float GRAVITY = 980 * 2;									// ������С

protected:
	std::string name;												// ��ɫ����
	int hp = 0;														// ��ɫ����ֵ
	float max_hp = 0;												// ��ɫ�������ֵ
	Vector2 pos;													// ��ɫ�ŵ�λ��
	Vector2 velocity;												// ��ɫ�ٶ�
	float logic_height = 0;											// ��ɫ�߼��߶�
	bool is_facing_right = true;									// ��ɫ�Ƿ��泯��
	bool enable_gravity = true;										// ��������ģ��
	bool is_invulnerable = false;									// ��ɫ�Ƿ�����޵�״̬
	Timer timer_invulnerable_status;								// �޵�״̬��ʱ��
	CollisionBox* hit_box = nullptr;								// ������ײ��
	CollisionBox* hurt_box = nullptr;								// �ܻ���ײ��
	Animation* current_animation = nullptr;							// ��ǰ��ɫ����
	float animation_magnification = 0;								// �����Ŵ���
	float animation_frame_delta = 0;								// ����֡ʱ��

};