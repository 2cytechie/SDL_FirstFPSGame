#include "collision_mgr.h"

CollisionMgr::CollisionMgr() = default;

CollisionMgr::~CollisionMgr() = default;

double max(double a, double b) {
	return a > b ? a : b;
}

double min(double a, double b) {
	return a > b ? b : a;
}

CollisionBox* CollisionMgr::creat() {
	CollisionBox* collision_box = new CollisionBox();

	collision_box_list.push_back(collision_box);

	return collision_box;
}

void CollisionMgr::destory(CollisionBox* collision_box) {
	collision_box_list.erase(std::remove(collision_box_list.begin(), 
		collision_box_list.end(), collision_box), collision_box_list.end());

	delete collision_box;
}

void CollisionMgr::process_collide() {
	for (CollisionBox* collision_box_src : collision_box_list) {
		if (!collision_box_src->enabled || collision_box_src->layer_dst == CollisionLayer::None) continue;

		for (CollisionBox* collision_box_dst : collision_box_list) {
			if (!collision_box_dst->enabled || collision_box_src == collision_box_dst || collision_box_src->layer_dst != collision_box_dst->layer_src)
				continue;

			bool is_collide_x = (max(collision_box_src->pos.x + collision_box_src->size.x / 2,
				collision_box_dst->pos.x + collision_box_dst->size.x / 2)
				- min(collision_box_src->pos.x - collision_box_src->size.x / 2,
					collision_box_dst->pos.x - collision_box_dst->size.x / 2))
				<= collision_box_src->size.x + collision_box_dst->size.x;

			bool is_collide_y = (max(collision_box_src->pos.y + collision_box_src->size.y / 2,
				collision_box_dst->pos.y + collision_box_dst->size.y / 2)
				- min(collision_box_src->pos.y - collision_box_src->size.y / 2,
					collision_box_dst->pos.y - collision_box_dst->size.y / 2))
				<= collision_box_src->size.y + collision_box_dst->size.y;

			if (is_collide_x && is_collide_y && collision_box_dst->on_collide)
			{
				collision_box_dst->on_collide(collision_box_src);
			}
		}
	}
}

void CollisionMgr::on_debug_render(Camera& camera) {
	for (CollisionBox* collision_box : collision_box_list)
	{
		SDL_Rect rect{
			collision_box->pos.x - collision_box->size.x / 2,
			collision_box->pos.y - collision_box->size.y / 2,
			collision_box->size.x,
			collision_box->size.y
		};
		SDL_Color color = collision_box->enabled ? SDL_Color{ 255, 195, 195,255 } : SDL_Color{ 115, 115, 175,255 };
		camera.draw_rect(&rect, color);
	}
}