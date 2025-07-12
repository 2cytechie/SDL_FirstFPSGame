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
	void on_render(SDL_Renderer* renderer);
	void on_input(const SDL_Event& msg);
	void on_exit();

private:
	SDL_Point window_size = { 1280,720 };		// ���ڴ�С

	int select_player = 0;
	std::vector<Text> instructions;				// ˵��
	Animation* attack_animation = nullptr;		// ��������
};
