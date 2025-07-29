#include "player.h"
#include "res_mgr.h"
#include "player_state_node.h"

Player::Player() {
    hp = 100;
    max_hp = 100;
    pos = Vector2(100, 100);

	hit_box->set_layer_src(CollisionLayer::None);
	hit_box->set_layer_dst(CollisionLayer::Enemy);

	hurt_box->set_layer_src(CollisionLayer::Player);
	hurt_box->set_layer_dst(CollisionLayer::None);

	hit_box->set_enabled(false);

    hurt_box->set_on_collide([&](const CollisionBox* box) {
        decrease_hp(box->get_damage());
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

	// 状态机  Attack  的时间不同放到不同角色类中添加
    state_machine.register_state(this, "Attack", new PlayerAttackState());
    state_machine.register_state(this, "Death", new PlayerDeathState());
    state_machine.register_state(this, "Idle", new PlayerIdleState());
    state_machine.register_state(this, "Jump", new PlayerJumpState());
    state_machine.register_state(this, "Run", new PlayerRunState());
    state_machine.register_state(this, "Dash", new PlayerDashState());

    state_machine.set_entry("Idle");
}

Player::~Player() = default;

void Player::init() {
    int damage = 1000 / hit_box->get_size().x;
    hit_box->set_damage(damage);

    block_box->set_size(hurt_box->get_size());

    animation_pool["Attack"] = ResMgr::instance()->find_animation(name + "_Attack");
    animation_pool["Death"] = ResMgr::instance()->find_animation(name + "_Death");
    animation_pool["Idle"] = ResMgr::instance()->find_animation(name + "_Idle");
    animation_pool["Jump"] = ResMgr::instance()->find_animation(name + "_Jump");
    animation_pool["Run"] = ResMgr::instance()->find_animation(name + "_Run");
}

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
            // 启用攻击碰撞箱
            hit_box->set_enabled(true);
        }
        break;

    case SDL_MOUSEBUTTONUP:
        if (msg.button.button == SDL_BUTTON_LEFT) {
            is_attack_key_down = false;
            // 禁用攻击碰撞箱
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

    Character::on_update(delta);
}

void Player::on_render(Camera& camera) {
    Character::on_render(camera);
}

void Player::on_hurt() {
    // 受击音效
    Mix_PlayChannel(-1, ResMgr::instance()->find_audio("ui_switch"), 0);
}

void Player::attack() {
    timer_attack_cd.restart();
    is_attack_cd_comp = false;
    hit_box->set_enabled(true);
}

void Player::jump() {
    velocity.y -= SPEED_JUMP;
    on_floor = false;
}

void Player::dash() {
    timer_dash_cd.restart();
    is_dash_cd_comp = false;
    velocity.x += is_facing_right ? SPEED_DASH : -SPEED_DASH;
}

void Player::hp_returning(int return_hp) {
    hp = hp + return_hp >= max_hp ? max_hp : hp + return_hp;
}

void Player::switch_state(const std::string& id) {
    state_machine.switch_state(id);
}