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
	Vector2 mouse_pos;					// �����Դ���λ��
	Vector2 window_pos;					// ����λ��

	bool is_left_button_down = false;	// �������Ƿ���
	bool is_select = false;				// �Ƿ�ѡ��
	Enemy* selected_enemy = nullptr;	// ѡ�еĵ���
	Item* selected_item = nullptr;		// ѡ�е���Ʒ

	bool mouse_in_box(CollisionBox* box);

};
