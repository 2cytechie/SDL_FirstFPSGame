#include "character.h"
#include "collision_mgr.h"
#include "res_mgr.h"

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
	if (hp <= 0) velocity.x = 0;
	if (enable_gravity) {
		velocity.y += GRAVITY * delta;
	}

	pos += velocity * delta;

	if (pos.y >= FLOOR_Y) {
		pos.y = FLOOR_Y;
		velocity.y = 0;
	}

	timer_invulnerable_status.on_update(delta);

	if (!current_animation) return;

	current_animation->on_update(delta);
	current_animation->set_pos(pos);
}

void Character::on_render(Camera& camera) {
	if (!current_animation) return;
	current_animation->set_interval(animation_frame_delta);
	current_animation->set_size(animation_magnification);
	current_animation->on_render(camera, is_facing_right);
}

// 受击后
void Character::on_hurt() {

}

void Character::set_animation(const std::string& id) {
	current_animation = ResMgr::instance()->find_animation(id);
	current_animation->reset();
}
