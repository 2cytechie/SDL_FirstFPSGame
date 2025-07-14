#pragma once

#include <vector>

#include "scene.h"
#include "animation.h"
#include "text.h"

class InstructionScene : public Scene {
public:
	InstructionScene();
	~InstructionScene();
	void on_enter();
	void on_update(float delta);
	void on_render(Camera& camera);
	void on_input(const SDL_Event& msg);
	void on_exit();
	void update();

private:
	SDL_Point window_size = { 1280,720 };		// 窗口大小

	int select_player = 0;
	std::vector<Text> instructions;				// 说明
	Text player_name;							// 玩家名字
	Animation* attack_animation = nullptr;		// 攻击动画

	TTF_Font* font_max = nullptr;
	TTF_Font* font = nullptr;
	TTF_Font* font_min = nullptr;
};
