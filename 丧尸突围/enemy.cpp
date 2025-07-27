#include "enemy.h"
#include "res_mgr.h"
#include "enemy_state_node.h"

Enemy::Enemy(Vector2 revive_pos) {
	pos_revive = revive_pos;

	hit_box->set_layer_src(CollisionLayer::None);
	hit_box->set_layer_dst(CollisionLayer::Player);

	hurt_box->set_layer_src(CollisionLayer::Enemy);
	hurt_box->set_layer_dst(CollisionLayer::None);

	hit_box->set_enabled(false);
	hit_box->set_on_collide([&](const CollisionBox* box) {
		velocity.y = 0;

		SDL_Log("Enemy hit");
		});

	hurt_box->set_on_collide([&](const CollisionBox* box) {
		on_hurt();
		//SDL_Log("Enemy hurt");
		});

	timer_attack_cd.set_wait_time(CD_ATTACK);
	timer_attack_cd.set_one_shot(true);
	timer_attack_cd.set_on_timeout([&]() {
		is_attack_cd_comp = true;
		hit_box->set_enabled(false);
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

void Enemy::on_update(float delta) {
	//state_machine.on_update(delta);

	Character::on_update(delta);
}

void Enemy::on_render(Camera& camera) {
	Character::on_render(camera);
}

void Enemy::switch_state(const std::string& id) {
	state_machine.switch_state(id);
}

void Enemy::on_hurt() {
	if (is_invulnerable) return;

	is_attacking = false;
	is_attack_cd_comp = true;
	state_machine.switch_state("TakeHit");
	// �ܻ���Ч
	Mix_PlayChannel(-1, ResMgr::instance()->find_audio("ui_switch"), 0);
}

void Enemy::attack() {
	velocity.x = 0;
	timer_attack_cd.restart();
	is_attack_cd_comp = false;
	hit_box->set_enabled(true);
}