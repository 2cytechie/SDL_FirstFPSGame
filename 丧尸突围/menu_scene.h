#pragma once

#include "text.h"
#include "scene.h"
#include "animation.h"

class MenuScene : public Scene {
public:
	MenuScene();
	~MenuScene();
	void on_enter();
	void on_update(float delta);
	void on_render(Camera& camera);
	void on_input(const SDL_Event& msg);
	void on_exit();
	void update();

private:
	Vector2 window_size = { 1280,720 };		// ���ڴ�С

	int select_game = 0;						// ѡ���
	Text start_game;							// ��ʼ��Ϸ
	Text playing_instrution;					// ��Ϸ�淨
	Text exit_game;								// �˳���Ϸ

	int select_player = 0;						// ѡ���ɫ(�μ�name.h)
	Animation* animation_player = nullptr;		// ��ɫ����
	Text player_name;							// ��ɫ����
	TTF_Font* font = nullptr;					// ���巽���������
};
