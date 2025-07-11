#pragma once

#include "scene.h"

class GameOverScene : public Scene {
public:
	GameOverScene();
	~GameOverScene();
	void on_enter();
	void on_update(const Camera& camera, float delta);
	void on_render(SDL_Renderer* renderer, const Camera& camera);
	void on_input(const SDL_Event& msg);
	void on_exit();

private:


};
