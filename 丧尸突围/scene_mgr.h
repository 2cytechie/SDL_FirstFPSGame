#pragma once

#include "singleton.h"
#include "scene.h"

#include <unordered_map>

class SceneMgr : public Singleton<SceneMgr> {
	friend Singleton<SceneMgr>;
public:
	enum class SceneType {
		Menu,
		Game,
		GameOver
	};

	void add(SceneType type, Scene* scene) {
		scene_loop[type] = scene;
	}

	void set_current_scene(SceneType type) {
		current_scene = scene_loop[type];
		current_scene->on_enter();
	}

	void switch_to(SceneType type) {
		current_scene->on_exit();
		current_scene = scene_loop[type];
		current_scene->on_enter();
	}

	void on_update(Camera& camera, float delta) {
		current_scene->on_update(camera, delta);
	}

	void on_render(SDL_Renderer* renderer, Camera& camera) {
		current_scene->on_render(renderer, camera);
	}
	void on_input(const SDL_Event& msg) {
		current_scene->on_input(msg);
	}

private:
	SceneMgr() = default;
	~SceneMgr() = default;
	Scene* current_scene = nullptr;
	std::unordered_map<SceneType, Scene*> scene_loop;
};