#pragma once

#include "res_mgr.h"
#include "character.h"

class Player : public Character {
public:

	Player();
	
	~Player();

	void init();

	int get_move_axis()const {
		// 1¡¢ÏòÓÒÒÆ¶¯  -1¡¢Ïò×óÒÆ¶¯   0¡¢¾²Ö¹
		return is_right_key_down - is_left_key_down;
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
		return is_on_floor() && is_jump_key_down;
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

private:
	StateMachine<Player> state_machine;			// Íæ¼ÒÂß¼­×´Ì¬»ú

	Timer timer_dash_cd;
	bool is_dashing = false;
	bool is_dash_cd_comp = true;				// ÉÁ±ÜÀäÈ´ÊÇ·ñ½áÊø

	Timer timer_attack_cd;
	bool is_attacking = false;
	bool is_attack_cd_comp = true;				// ¹¥»÷ÀäÈ´ÊÇ·ñ½áÊø

	bool is_left_key_down = false;
	bool is_right_key_down = false;
	bool is_jump_key_down = false;
	bool is_dash_key_down = false;
	bool is_attack_key_down = false;

private:
	const float CD_DASH = 0.5f;
	const float CD_ATTACK = 0.3f;
	const float SPEED_RUN = 300.0f;
	const float SPEED_JUMP = 780.0f;
	const float SPEED_DASH = 2000.0f;
};
