#pragma once
#include "res_mgr.h"
#include "character.h"

class Player : public Character {
public:

	Player();
	
	~Player();

	void init();

	int get_move_axis()const {
		// 1、向右移动  -1、向左移动   0、静止
		return is_right_key_down - is_left_key_down;
	}

	void reset() {
		hp = max_hp;
		is_left_key_down = false;
		is_right_key_down = false;
		is_jump_key_down = false;
		is_dash_key_down = false;
		is_attack_key_down = false;
		pos = Vector2(200, 0);
		state_machine.switch_state("Idle");
	}

	void set_dashing(bool flag) {
		is_dashing = flag;
		if (flag) {
			velocity.x = 0;
		}
	}

	void set_attacking(bool flag) {
		is_attacking = flag;
	}

	bool get_attacking() {
		return is_attacking;
	}

	float get_current_animation_time() {
		if (current_animation) {
			return current_animation->get_time();
		}
		return 0.0f;
	}

	bool get_dashing() {
		return is_dashing;
	}

	bool can_attack()const {
		return is_attack_cd_comp && !is_attacking && is_attack_key_down;
	}

	bool can_jump() {
		if (is_on_floor()) {
			jump_count = 0;
		}
		return is_jump_key_down && jump_count < max_jump_count;
	}

	bool can_dash()const {
		return is_dash_cd_comp && !is_dashing && is_dash_key_down;
	}

	void set_current_animation(std::string state);
	void switch_state(const std::string& id);

	void on_input(const SDL_Event& msg) override;
	void on_update(float delta) override;
	void on_render(Camera& camera)override;

	void on_hurt() override;

	void attack();
	void jump();
	void dash();
	void hp_returning(int return_hp);

private:
	StateMachine<Player> state_machine;			// 玩家逻辑状态机

	int jump_count = 0;							// 跳跃次数
	int max_jump_count = 2;						// 最大跳跃次数

	Timer timer_dash_cd;
	bool is_dashing = false;
	bool is_dash_cd_comp = true;				// 闪避冷却是否结束

	Timer timer_attack_cd;
	bool is_attacking = false;
	bool is_attack_cd_comp = true;				// 攻击冷却是否结束

	bool is_left_key_down = false;
	bool is_right_key_down = false;
	bool is_jump_key_down = false;
	bool is_dash_key_down = false;
	bool is_attack_key_down = false;

private:
	const float CD_DASH = 0.5f;
	const float CD_ATTACK = 0.3f;
	const float SPEED_RUN = 300.0f;
	const float SPEED_JUMP = 800.0f;
	const float SPEED_DASH = 2000.0f;
};
