#pragma once

#include "vector2.h"
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

	int get_hp() {
		return hp;
	}

	int get_max_hp() {
		return max_hp;
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

	CollisionBox* get_block_box() {
		return block_box;
	}

	void set_on_floor(bool flag) {
		on_floor = flag;
	}

	bool is_on_floor()const {
		return on_floor;
	}

	void make_invulnerable() {
		is_invulnerable = true;
		timer_invulnerable_status.restart();
	}

	virtual void on_input(const SDL_Event& msg);
	virtual void on_update(float delta);
	virtual void on_render(Camera& camera);

	virtual void on_hurt();
	virtual void decrease_hp(int damage);

	void set_animation(const std::string& id);


protected:
	const float GRAVITY = 980 * 2;									// ������С

protected:
	std::string name;												// ��ɫ����
	int hp = 0;														// ��ɫ����ֵ
	int max_hp = 0;												// ��ɫ�������ֵ
	Vector2 pos;													// ��ɫ�ŵ�λ��
	Vector2 velocity;												// ��ɫ�ٶ�
	bool on_floor = false;											// ��ɫ�Ƿ��ڵذ���
	bool is_facing_right = true;									// ��ɫ�Ƿ��泯��
	bool enable_gravity = true;										// ��������ģ��
	bool is_invulnerable = false;									// ��ɫ�Ƿ�����޵�״̬
	Timer timer_invulnerable_status;								// �޵�״̬��ʱ��
	CollisionBox* block_box = nullptr;								// �赲��ײ��
	CollisionBox* hit_box = nullptr;								// ������ײ��
	CollisionBox* hurt_box = nullptr;								// �ܻ���ײ��
	Animation* current_animation = nullptr;							// ��ǰ��ɫ����
	std::unordered_map<std::string, Animation*> animation_pool;		// ������
	float animation_magnification = 1;								// �����Ŵ���
	float animation_frame_delta = 0;								// ����֡ʱ��

};