#include "enemy.h"
#include "res_mgr.h"
#include "enemy_state_node.h"

Enemy::Enemy(Vector2 revive_pos) {
	pos_revive = revive_pos;
	pos = revive_pos;

	hit_box->set_layer_src(CollisionLayer::None);
	hit_box->set_layer_dst(CollisionLayer::Player);

	hurt_box->set_layer_src(CollisionLayer::Enemy);
	hurt_box->set_layer_dst(CollisionLayer::None);

	hit_box->set_enabled(false);

	hurt_box->set_on_collide([&](const CollisionBox* box) {
		decrease_hp(box->get_damage());
		});

	timer_attack_cd.set_wait_time(CD_ATTACK);
	timer_attack_cd.set_one_shot(true);
	timer_attack_cd.set_on_timeout([&]() {
		is_attack_cd_comp = true;
		hit_box->set_enabled(false);
		});

	timer_render_hp.set_wait_time(5.0f);
    timer_render_hp.set_one_shot(true);
	timer_render_hp.set_on_timeout([&]() {
		is_render_hp = false;
		});

	state_machine.register_state(this, "Attack", new EnemyAttackState());
	state_machine.register_state(this, "Death", new EnemyDeathState());
	state_machine.register_state(this, "Idle", new EnemyIdleState());
	state_machine.register_state(this, "TakeHit", new EnemyTakeHitState());
	state_machine.register_state(this, "Walk", new EnemyWalkState());
	state_machine.register_state(this, "Pursuit", new EnemyPursuitState());
	state_machine.register_state(this, "Return", new EnemyReturnState());

	state_machine.set_entry("Idle");
}

void Enemy::init() {
	int damage = 1000 / hit_box->get_size().x;
	hit_box->set_damage(damage);

	block_box->set_size(hurt_box->get_size());

	animation_pool["Attack"] = ResMgr::instance()->find_animation(name + "_Attack");
	animation_pool["Death"] = ResMgr::instance()->find_animation(name + "_Death");
	animation_pool["Idle"] = ResMgr::instance()->find_animation(name + "_Idle");
	animation_pool["Run"] = ResMgr::instance()->find_animation(name + "_Run");
	animation_pool["TakeHit"] = ResMgr::instance()->find_animation(name + "_TakeHit");
}

void Enemy::on_update(float delta) {
	state_machine.on_update(delta);

	Character::on_update(delta);
}

void Enemy::on_render(Camera& camera) {
	Character::on_render(camera);
	
	if (is_render_hp) {
		// 绘制血条
		SDL_Color color_rect = { 128,0,0,255 };
		SDL_Color color_hp = { 255,0,0,255 };

		Vector2 size = hurt_box->get_size();
		SDL_Rect rect_rect = {
			pos.x - max_hp / 2,
			pos.y - size.y - 20,
			max_hp,
			10
		};
		SDL_Rect rect_hp = {
			pos.x - max_hp / 2,
			pos.y - size.y - 20,
			hp / max_hp,
			10
		};
		camera.draw_rect(&rect_rect, color_rect);
		camera.fill_rect(&rect_hp, color_hp);
	}
}

void Enemy::switch_state(const std::string& id) {
	state_machine.switch_state(id);
}

void Enemy::on_hurt() {
	if (is_invulnerable) return;

	// 绘制血条
	is_render_hp = true;

	// 转换受击动画
	is_attacking = false;
	is_attack_cd_comp = true;
	state_machine.switch_state("TakeHit");
	// 受击音效
	Mix_PlayChannel(-1, ResMgr::instance()->find_audio("ui_switch"), 0);
}

void Enemy::attack() {
	velocity.x = 0;
	timer_attack_cd.restart();
	is_attack_cd_comp = false;
	hit_box->set_enabled(true);
}

void Enemy::take_hit() {

}

void Enemy::walk() {
	is_facing_right = (pos.x - pos_revive.x) < 0;
	velocity.x = is_facing_right ? SPEED_WALK : -SPEED_WALK;
}

void Enemy::idle() {
	velocity.x = 0;
}

void Enemy::pursuit(Vector2& player_pos) {
	is_facing_right = (player_pos.x - pos.x) > 0;
	velocity.x = is_facing_right ? SPEED_PURSUIT : -SPEED_PURSUIT;
}

void Enemy::return_revive() {
	is_facing_right = (pos.x - pos_revive.x) < 0;
	velocity.x = is_facing_right ? SPEED_WALK : -SPEED_WALK;
}