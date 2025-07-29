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
	const float GRAVITY = 980 * 2;									// 重力大小

protected:
	std::string name;												// 角色名字
	int hp = 0;														// 角色生命值
	int max_hp = 0;												// 角色最大生命值
	Vector2 pos;													// 角色脚底位置
	Vector2 velocity;												// 角色速度
	bool on_floor = false;											// 角色是否在地板上
	bool is_facing_right = true;									// 角色是否面朝右
	bool enable_gravity = true;										// 启用重力模拟
	bool is_invulnerable = false;									// 角色是否进入无敌状态
	Timer timer_invulnerable_status;								// 无敌状态定时器
	CollisionBox* block_box = nullptr;								// 阻挡碰撞箱
	CollisionBox* hit_box = nullptr;								// 攻击碰撞箱
	CollisionBox* hurt_box = nullptr;								// 受击碰撞箱
	Animation* current_animation = nullptr;							// 当前角色动画
	std::unordered_map<std::string, Animation*> animation_pool;		// 动画池
	float animation_magnification = 1;								// 动画放大倍数
	float animation_frame_delta = 0;								// 动画帧时间

};