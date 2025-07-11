#pragma once

#include <SDL.h>

#include "camera.h"

class Scene {
public:
	Scene() = default;
	~Scene() = default;

	virtual void on_enter() {}
	virtual void on_update(Camera& camera, float delta) {}
	virtual void on_render(SDL_Renderer* renderer, Camera& camera) {}
	virtual void on_input(const SDL_Event& msg) {}
	virtual void on_exit() {}

private:


};