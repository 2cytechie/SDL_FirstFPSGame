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
	Vector2 window_size = { 1280,720 };		// 窗口大小

	int select_game = 0;
	Text game_over;								// 游戏结束
	Text resume;								// 继续游戏
	Text menu;									// 游戏菜单
	Text exit_game;								// 退出游戏
	TTF_Font* font_max = nullptr;				// 字体方便退出时销毁
	TTF_Font* font = nullptr;
	
};
