#include "item.h"
#include "res_mgr.h"
#include "level_mgr.h"

Item::Item(Vector2 p) {
	pos = p;
	block_box = CollisionMgr::instance()->creat();
	block_box->set_layer_src(CollisionLayer::None);
	block_box->set_layer_dst(CollisionLayer::Item);
}

Item::~Item() {
	CollisionMgr::instance()->destory(block_box);
}

void Item::init() {
	animation = ResMgr::instance()->find_animation(name);
	animation->set_pos(pos);
	animation->set_size(animation_magnification);
	animation->set_interval(animation_frame_delta);

	Vector2 pos_box{
		pos.x,
		pos.y - block_box->get_size().y / 2
	};
	block_box->set_pos(pos_box);
}

void Item::on_update(float delta) {
	if (!animation) return;
	animation->on_update(delta);
}

void Item::on_render(Camera& camera) {
	if (!animation) return;
	animation->on_render(camera, is_facing_right);
}