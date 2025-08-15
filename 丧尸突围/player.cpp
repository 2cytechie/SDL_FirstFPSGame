#include "player.h"
#include "res_mgr.h"
#include "player_state_node.h"

Player::Player() {
    max_hp = 75;
    pos = Vector2(200, 100);

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

Player::~Player() {
    TTF_CloseFont(font);
}

void Player::init() {
    hp = max_hp;
    Character::attack = 1000 / hit_box->get_size().x;
    font = TTF_OpenFont("resources/IPix.ttf", 10);
    hit_box->set_damage(Character::attack);

    block_box->set_size(hurt_box->get_size());

    animation_pool["Attack"] = ResMgr::instance()->copy_animation(name + "_Attack");
    animation_pool["Death"] = ResMgr::instance()->copy_animation(name + "_Death");
    animation_pool["Idle"] = ResMgr::instance()->copy_animation(name + "_Idle");
    animation_pool["Jump"] = ResMgr::instance()->copy_animation(name + "_Jump");
    animation_pool["Run"] = ResMgr::instance()->copy_animation(name + "_Run");
}

void Player::set_current_animation(std::string state) {
    std::string file_name = name + "_" + state;
    current_animation = animation_pool[file_name];
    current_animation->reset();
    current_animation->set_loop(true);
}

void Player::reset() {
    is_left_key_down = false;
    is_right_key_down = false;
    is_jump_key_down = false;
    is_dash_key_down = false;
    is_attack_key_down = false;
    is_attack_cd_comp = true;
    is_attacking = false;

    hp = max_hp;
    pos = Vector2(200, 0);
    velocity = Vector2(0, 0);
    state_machine.switch_state("Idle");
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
        case SDLK_F1:
            if (DEBUG) {
                plus_max_hp(25);
                plus_attack(5);
                SDL_Log("plus max_hp and attack");
            }
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

    if (velocity.y > 5000) {
        hp = 0;
    }

    timer_dash_cd.on_update(delta);
    timer_attack_cd.on_update(delta);

    Character::on_update(delta);
}

void Player::on_render(Camera& camera) {
    Character::on_render(camera);

    // UI
    // 绘制血条  和攻击力
    SDL_Color color_rect = { 128,0,0,255 };
    SDL_Color color_hp = { 200,0,0,255 };

    Vector2 window_size = camera.get_window_size();
    Vector2 camera_pos = camera.get_pos();
    std::string tex_hp = u8"血量 : " + std::to_string(hp);
    text_hp.set(tex_hp.c_str(), font, Vector2(camera_pos.x + 20, camera_pos.y + window_size.y - 30), Text::TextType::Left, color_hp);
    SDL_Rect rect_max_hp = {
        camera_pos.x + 100,
        camera_pos.y + window_size.y - 35,
        max_hp,
        10
    };
    SDL_Rect rect_hp = {
        camera_pos.x + 100,
        camera_pos.y + window_size.y - 35,
        hp > 0 ? hp : 0,
        10
    };
    camera.draw_text(&text_hp);
    camera.draw_rect(&rect_max_hp, color_rect);
    camera.fill_rect(&rect_hp, color_hp);

    SDL_Color color_attack = { 0,0,128,255 };
    std::string tex_attack = u8"攻击力 : " + std::to_string(Character::attack);
    text_attack.set(tex_attack.c_str(), font, Vector2(camera_pos.x + 20, camera_pos.y + window_size.y - 15), Text::TextType::Left, color_attack);
    SDL_Rect rect_attack = {
        camera_pos.x + 100,
        camera_pos.y + window_size.y - 20,
        Character::attack * 3,
        10
    };
    camera.draw_text(&text_attack);
    camera.fill_rect(&rect_attack, color_attack);
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
    is_jump_key_down = false;
    jump_count++;
    velocity.y = 0;
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

    if (DEBUG) {
        SDL_Log("player returning %d hp", return_hp);
    }
}

void Player::switch_state(const std::string& id) {
    state_machine.switch_state(id);
}