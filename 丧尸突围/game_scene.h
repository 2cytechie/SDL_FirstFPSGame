#pragma once

#include "scene.h"

class GameScene : public Scene {
public:
	GameScene();
	~GameScene();
	void on_enter();
	void on_update(float delta);
	void on_render(SDL_Renderer* renderer);
	void on_input(const SDL_Event& msg);
	void on_exit();

private:


};
