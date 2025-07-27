#pragma once

#include "camera.h"
#include "singleton.h"
#include "collision_box.h"

#include <SDL.h>

class CollisionMgr :public Singleton<CollisionMgr> {
	friend Singleton<CollisionMgr>;

public:
	CollisionBox* creat();
	void destory(CollisionBox* collision);
	void process_collide();			// ¼ì²âÅö×²
	void on_debug_render(Camera& camera);

private:
	CollisionMgr();
	~CollisionMgr();

	std::vector<CollisionBox*> collision_box_list;

};