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

	Vector2 get_logic_center()const {
		return Vector2(pos.x, pos.y - logic_height / 2);
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
	virtual void on_render(SDL_Renderer* renderer);

	virtual void on_hurt();

	void switch_state(const std::string& id);
	void set_animation(const std::string& id);


protected:
	const float FLOOR_Y = 620;										// 地板竖直方向坐标
	const float GRAVITY = 980 * 2;									// 重力大小

protected:
	int hp;															// 角色生命值
	float max_hp;													// 角色最大生命值
	Vector2 pos;													// 角色脚底位置
	Vector2 velocity;												// 角色速度
	float logic_height = 0;											// 角色逻辑高度
	bool is_facing_right = true;									// 角色是否面朝右
	StateMachine state_machine;										// 角色逻辑状态机
	bool enable_gravity = true;										// 启用重力模拟
	bool is_invulnerable = false;									// 角色是否进入无敌状态
	Timer timer_invulnerable_status;								// 无敌状态定时器
	CollisionBox* hit_box = nullptr;								// 攻击碰撞箱
	CollisionBox* hurt_box = nullptr;								// 受击碰撞箱
	Animation* current_animation = nullptr;							// 当前角色动画

};