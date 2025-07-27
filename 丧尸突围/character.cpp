#include "character.h"
#include "collision_mgr.h"
#include "res_mgr.h"

Character::Character() {
	hit_box = CollisionMgr::instance()->creat();
	hurt_box = CollisionMgr::instance()->creat();
	block_box = CollisionMgr::instance()->creat();

	block_box->set_layer_src(CollisionLayer::Item);
	block_box->set_layer_dst(CollisionLayer::None);

	block_box->set_on_collide([&](const CollisionBox* box) {
		Vector2 my_pos = block_box->get_pos();
		Vector2 my_size = block_box->get_size();
		Vector2 box_pos = box->get_pos();
		Vector2 box_size = box->get_size();
		// 掉落
		if (pos.y <= box_pos.y && velocity.y >= 0) {
			pos.y = box->get_pos().y - box->get_size().y / 2;
			velocity.y = 0;
			on_floor = true;
		}
		// 计算水平方向的重叠
		float overlap_x = std::min(
			my_pos.x + my_size.x / 2 - (box_pos.x - box_size.x / 2),
			box_pos.x + box_size.x / 2 - (my_pos.x - my_size.x / 2)
		);

		if (on_floor && pos.y > box_pos.y - box_size.y / 2) {
			if (velocity.x > 0) {
				pos.x -= overlap_x;
			}
			else if (velocity.x < 0) {
				pos.x += overlap_x;
			}
		}
		});

	// 每 0.5 秒最多受击一次
	timer_invulnerable_status.set_wait_time(0.5f);
	timer_invulnerable_status.set_one_shot(true);
	timer_invulnerable_status.set_on_timeout([&]() {
		is_invulnerable = false;
		});
}

Character::~Character() {
	CollisionMgr::instance()->destory(hit_box);
	CollisionMgr::instance()->destory(hurt_box);
	CollisionMgr::instance()->destory(block_box);
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

	timer_invulnerable_status.on_update(delta);

	Vector2 pos_hurt_box = {
		pos.x,
		pos.y - hurt_box->get_size().y / 2
	};
	hurt_box->set_pos(pos_hurt_box);
	block_box->set_pos(pos_hurt_box);

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
