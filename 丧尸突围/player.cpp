#include "player.h"
#include "res_mgr.h"
#include "player_state_node.h"

Player::Player() {
	hit_box->set_layer_src(CollisionLayer::Item);
	hit_box->set_layer_dst(CollisionLayer::Enemy);

	hurt_box->set_layer_src(CollisionLayer::Player);
	hurt_box->set_layer_dst(CollisionLayer::None);

	hit_box->set_enabled(false);
	hit_box->set_on_collide([&]() {
		velocity.y = 0;
		});

	timer_dash_cd.set_wait_time(CD_DASH);
	timer_dash_cd.set_on_timeout([&]() {
		is_dash_cd_comp = true;
		});

	timer_attack_cd.set_wait_time(CD_ATTACK);
	timer_attack_cd.set_one_shot(true);
	timer_attack_cd.set_on_timeout([&]() {
		is_attack_cd_comp = true;
        hit_box->set_enabled(false);
		});

	// ×´Ì¬»ú
    state_machine.register_state(this, "Attack", new PlayerAttackState());
    state_machine.register_state(this, "Death", new PlayerDeathState());
    state_machine.register_state(this, "Idle", new PlayerIdleState());
    state_machine.register_state(this, "Jump", new PlayerJumpState());
    state_machine.register_state(this, "Run", new PlayerRunState());
    state_machine.register_state(this, "Dash", new PlayerDashState());

    state_machine.set_entry("Idle");
}

Player::~Player() = default;

void Player::set_current_animation(std::string state) {
    std::string file_name = name + "_" + state;
    current_animation = ResMgr::instance()->find_animation(file_name);
    current_animation->reset();
    current_animation->set_loop(true);
}

void Player::on_input(const SDL_Event& msg) {
    if (hp <= 0) return;

    switch (msg.type) {
    case SDL_KEYDOWN:
        switch (msg.key.keysym.sym) {
        case SDLK_UP:
        case SDLK_w:
        case SDLK_SPACE:
            is_jump_key_down = true;
            break;
        case SDLK_DOWN:
        case SDLK_s:
        case SDLK_LSHIFT:
            is_dash_key_down = true;
            break;
        case SDLK_LEFT:
        case SDLK_a:
            is_left_key_down = true;
            break;
        case SDLK_RIGHT:
        case SDLK_d:
            is_right_key_down = true;
            break;
        }
        break;

    case SDL_KEYUP:
        switch (msg.key.keysym.sym) {
        case SDLK_UP:
        case SDLK_w:
        case SDLK_SPACE:
            is_jump_key_down = false;
            break;
        case SDLK_DOWN:
        case SDLK_s:
        case SDLK_LSHIFT:
            is_dash_key_down = false;
            break;
        case SDLK_LEFT:
        case SDLK_a:
            is_left_key_down = false;
            break;
        case SDLK_RIGHT:
        case SDLK_d:
            is_right_key_down = false;
            break;
        }
        break;

    case SDL_MOUSEBUTTONDOWN:
        if (msg.button.button == SDL_BUTTON_LEFT) {
            is_attack_key_down = true;
            // ÆôÓÃ¹¥»÷Åö×²Ïä
            hit_box->set_enabled(true);
        }
        break;

    case SDL_MOUSEBUTTONUP:
        if (msg.button.button == SDL_BUTTON_LEFT) {
            is_attack_key_down = false;
            // ½ûÓÃ¹¥»÷Åö×²Ïä
            hit_box->set_enabled(false);
        }
        break;
    }
}

void Player::on_update(float delta) {
    state_machine.on_update(delta);

    if (hp > 0 && !is_dashing) {
        velocity.x = get_move_axis() * SPEED_RUN;
    }

    if (get_move_axis() != 0) {
        is_facing_right = (get_move_axis() > 0);
    }

    timer_dash_cd.on_update(delta);
    timer_attack_cd.on_update(delta);

    if (current_animation) {
        current_animation->on_update(delta);
    }

    Vector2 pos_hurt_box = {
        pos.x - hurt_box->get_size().x / 2,
        pos.y - hurt_box->get_size().y
    };
    hurt_box->set_pos(pos_hurt_box);

    Character::on_update(delta);
}

void Player::on_render(Camera& camera) {
    Character::on_render(camera);
}

void Player::on_hurt() {
    // ÊÜ»÷ÒôÐ§
    Mix_PlayChannel(-1, ResMgr::instance()->find_audio("ui_switch"), 0);
}

void Player::attack() {
    timer_attack_cd.restart();
    is_attack_cd_comp = false;
    hit_box->set_enabled(true);
}

void Player::jump() {
    velocity.y -= SPEED_JUMP;
}

void Player::dash() {
    timer_dash_cd.restart();
    is_dash_cd_comp = false;
    velocity.x += is_facing_right ? SPEED_DASH : -SPEED_DASH;
}

void Player::switch_state(const std::string& id) {
    state_machine.switch_state(id);
}