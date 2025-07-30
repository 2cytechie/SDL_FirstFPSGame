#pragma once

#include "scene.h"
#include "text.h"

class GameOverScene : public Scene {
public:
	GameOverScene();
	~GameOverScene();
	void on_enter();
	void on_update(float delta);
	void on_render(Camera& camera);
	void on_input(const SDL_Event& msg);
	void on_exit();

private:
	Vector2 window_size = { 1280,720 };		// ���ڴ�С

	int select_game = 0;
	Text game_over;								// ��Ϸ����
	Text resume;								// ������Ϸ
	Text menu;									// ��Ϸ�˵�
	Text exit_game;								// �˳���Ϸ
	TTF_Font* font_max = nullptr;				// ���巽���˳�ʱ����
	TTF_Font* font = nullptr;
	
};
