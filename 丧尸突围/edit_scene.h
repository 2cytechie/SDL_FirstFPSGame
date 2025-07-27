#pragma once

#include "scene.h"
#include "collision_box.h"
#include "enemy.h"
#include "item.h"

class EditScene : public Scene {
public:
	EditScene() = default;
	~EditScene() = default;
	void on_enter();
	void on_update(float delta);
	void on_render(Camera& camera);
	void on_input(const SDL_Event& msg);
	void on_exit();
	void save();

private:
	Vector2 mouse_pos;				// 鼠标相对窗口位置
	Vector2 window_pos;				// 窗口位置
	Timer timer_generate;			// 最短生成时间 防止生成物品过多
	bool is_generating = false;		// 是否正在生成物品

	bool is_select = false;			// 是否选中
	Enemy* selected_enemy = nullptr;// 选中的敌人
	Item* selected_item = nullptr;	// 选中的物品

	bool mouse_in_box(CollisionBox* box);

};
