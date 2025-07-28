#pragma once

#include "character.h"

class Enemy : public Character {
public:
	Enemy(Vector2 revive_pos);

	~Enemy() = default;

	void init();

	float get_current_animation_time() {
		if (current_animation) {
			return current_animation->get_time();
		}
		return 0.0f;
	}

	void set_attacking(bool flag) {
		is_attacking = flag;
	}

	bool get_attacking() {
		return is_attacking;
	}

	bool can_attack(const Vector2& player_pos) {
		Vector2 direction = player_pos - pos;
		bool in_range = (direction.length() <= ATTACK_DIS);
		bool facing_player = (is_facing_right && direction.x > 0) ||
			(!is_facing_right && direction.x < 0);

		return !is_attacking && in_range && facing_player;
	}

	bool can_pursuit(const Vector2& player_pos) {
		if ((pos - pos_revive).length() > MAX_PURSUIT_DIS) {
			return false;
		}
		Vector2 distance = player_pos - pos;
		return distance.length() < PURSUIT_DIS;
	}

	bool need_return(const Vector2& player_pos) {
		return (player_pos - pos).length() > PURSUIT_DIS;
	}

	bool finish_retrun() {
		return std::abs(pos.x - pos_revive.x) < 10.0f;
	}

	Vector2& get_revive_pos() {
		return pos_revive;
	}

	void on_update(float delta) override;
	void on_render(Camera& camera)override;

	void switch_state(const std::string& id);

	void on_hurt() override;

	void attack();
	void take_hit();
	void walk();
	void idle();
	void pursuit(Vector2& player_pos);
	void return_revive();

private:
	StateMachine<Enemy> state_machine;			// 敌人逻辑状态机

	Timer timer_attack_cd;
	bool is_attacking = false;
	bool is_attack_cd_comp = true;				// 攻击冷却是否结束

	Vector2 pos_revive;							// 出生点
	bool is_pursuiting = false;

	const float SPEED_WALK = 150.0f;			// 行走速度
	const float SPEED_PURSUIT = 250.0f;			// 追击速度
	const float ATTACK_DIS = 100.0f;			// 攻击距离
	const float CD_ATTACK = 2.5f;				// 攻击CD
	const float PURSUIT_DIS = 400;				// 追击距离
	const float MAX_PURSUIT_DIS = 1000;			// 最大追击距离

};
