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
    if (json.contains("name")) {
        name = json["name"].get<std::string>();
    }
    else {
        name = "unknown_item";
        SDL_Log("Item name ERROR");
    }
    if (json.contains("pos")) {
        pos = Vector2(json["pos"][0].get<float>(), json["pos"][1].get<float>());
    }
    else {
        pos = Vector2(0.0f, 0.0f);
        SDL_Log("Item pos Error : name = %s", name.c_str());
    }
    if (json.contains("is_block")) {
        is_block = json["is_block"].get<bool>();
    }
    else {
        is_block = false;
        SDL_Log("Item is_block Error : name = %s", name.c_str());
    }
    if (json.contains("block_box_size")) {
        block_box_size = Vector2(json["block_box_size"][0].get<float>(), json["block_box_size"][1].get<float>());
    }
    else {
        block_box_size = Vector2(0.0f, 0.0f);
        SDL_Log("Item block_box_size Error : name = %s", name.c_str());
    }
    if (json.contains("animation_magnification")) {
        animation_magnification = json["animation_magnification"].get<float>();
    }
    else {
        animation_magnification = 1.0f;
        SDL_Log("Item animation_magnification Error : name = %s", name.c_str());
    }
    if (json.contains("animation_frame_delta")) {
        animation_frame_delta = json["animation_frame_delta"];
    }
    else {
        animation_frame_delta = 0.1f;
        SDL_Log("Item animation_frame_delta Error : name = %s", name.c_str());
    }

    init();
}

Item::~Item() {
	CollisionMgr::instance()->destory(block_box);
}

void Item::init() {
	animation = ResMgr::instance()->find_animation(name);
    if (animation) {
        animation->set_size(animation_magnification);
        animation->set_interval(animation_frame_delta);
    }

	block_box = CollisionMgr::instance()->creat();
	block_box->set_layer_src(CollisionLayer::None);
	block_box->set_layer_dst(CollisionLayer::Item);
	block_box->set_enabled(is_block);

	// �༭ģʽ
    if (animation) {
        Vector2 size = animation->get_size();
        block_box_size = size;
    }

	block_box->set_size(block_box_size);
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
	if (!animation) return;
	animation->on_render(camera, is_facing_right);
}

nlohmann::json Item::to_json() const {
	return nlohmann::json{
		{"name", name},
		{"pos", {pos.x, pos.y}},
		{"is_block", is_block},
		{"block_box_size", {block_box_size.x, block_box_size.y}},
		{"animation_magnification", animation_magnification},
		{"animation_frame_delta", animation_frame_delta}
	};
}