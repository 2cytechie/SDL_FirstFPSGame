#include "item.h"
#include "res_mgr.h"

Item::Item(Vector2 p) {
	pos = p;
	block_box = CollisionMgr::instance()->creat();
	block_box->set_layer_src(CollisionLayer::None);
	block_box->set_layer_dst(CollisionLayer::Item);
}

Item::Item(std::string name, Vector2 p) {
	this->name = name;
    pos = p;

	init();
}

Item::Item(nlohmann::json& json) {
	name = json["name"];
	pos = Vector2(json["pos"][0], json["pos"][1]);
	is_block = json["is_block"];
	animation_magnification = json["animation_magnification"];
	animation_frame_delta = json["animation_frame_delta"];
	relative_camera_speed = json["relative_camera_speed"];

	init();
}

Item::~Item() {
	CollisionMgr::instance()->destory(block_box);
}

void Item::init() {
	animation = ResMgr::instance()->find_animation(name);
	animation->set_size(animation_magnification);
	animation->set_interval(animation_frame_delta);

	block_box = CollisionMgr::instance()->creat();
	block_box->set_layer_src(CollisionLayer::None);
	block_box->set_layer_dst(CollisionLayer::Item);
	block_box->set_enabled(is_block);
	Vector2 size = animation->get_size();
	block_box->set_size(size);
}

void Item::on_update(float delta) {
	if (!animation) return;
	animation->set_pos(pos);
	animation->on_update(delta);

	Vector2 pos_box{
		pos.x,
		pos.y - block_box->get_size().y / 2
	};
	block_box->set_pos(pos_box);
}

void Item::on_render(Camera& camera) {
	pos -= camera.get_camera_move() * relative_camera_speed;

	if (!animation) return;
	animation->on_render(camera, is_facing_right);
}

nlohmann::json Item::to_json() const {
	return nlohmann::json{
		{"name", name},
		{"pos", {pos.x, pos.y}},
		{"is_block", is_block},
		{"animation_magnification", animation_magnification},
		{"animation_frame_delta", animation_frame_delta},
		{"relative_camera_speed", relative_camera_speed}
	};
}