#pragma once

#include "scene.h"
#include "level.h"

class GameOnScene : public Scene {
public:
	GameOnScene();
	~GameOnScene();
	void on_enter();
	void on_update(float delta);
	void on_render(Camera& camera);
	void on_input(const SDL_Event& msg);
	void on_exit();

private:
	int N_level = 1;

};
