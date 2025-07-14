#include "character.h"
#include "collision_mgr.h"

Character::Character() {
	hit_box = CollisionMgr::instance()->creat();
	hurt_box = CollisionMgr::instance()->creat();

	// 每秒最多受击一次
	timer_invulnerable_status.set_wait_time(1.0f);
	timer_invulnerable_status.set_one_shot(true);
	timer_invulnerable_status.set_on_timeout([&]() {
		is_invulnerable = false;
		});
}

Character::~Character() {
	CollisionMgr::instance()->distory(hit_box);
	CollisionMgr::instance()->distory(hurt_box);
}

void Character::decrease_hp(int damage) {
	if (is_invulnerable) return;
	hp -= damage;
	if (hp > 0) {
		make_invulnerable();
	}
	on_hurt();
}

void Character::on_input(const SDL_Event& msg) {}

void Character::on_update(float delta) {
	state_machine.on_update(delta);

	if (hp <= 0) velocity.x = 0;
	if (enable_gravity) {
		velocity.y += GRAVITY * delta;
	}

	pos += velocity * delta;

	if (pos.y >= FLOOR_Y) {
		pos.y = FLOOR_Y;
		velocity.y = 0;
	}

	// 防止超出屏幕
	if (pos.x <= 0)pos.x = 0;
	

	hurt_box->set_pos(get_logic_center());

	timer_invulnerable_status.on_update(delta);

	if (!current_animation) return;
}

void Character::on_render(SDL_Renderer* renderer) {

}

void Character::on_hurt() {

}

void Character::switch_state(const std::string& id) {

}
void Character::set_animation(const std::string& id) {

}
