#pragma once

#include "camera.h"

class Scene {
public:
	Scene() = default;
	~Scene() = default;

	virtual void on_enter() {}
	virtual void on_update(float delta) {}
	virtual void on_render(Camera& camera) {}
	virtual void on_input(const SDL_Event& msg) {}
	virtual void on_exit() {}

private:


};