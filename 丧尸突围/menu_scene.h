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
	Vector2 window_size = { 1280,720 };		// 窗口大小

	int select_game = 0;						// 选择框
	Text start_game;							// 开始游戏
	Text playing_instrution;					// 游戏玩法
	Text exit_game;								// 退出游戏

	int select_player = 0;						// 选择角色(参见name.h)
	Animation* animation_player = nullptr;		// 角色动画
	Text player_name;							// 角色名字
	TTF_Font* font = nullptr;					// 字体方便进行销毁
};
