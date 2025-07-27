#pragma once

#include "singleton.h"
#include "scene.h"

#include <unordered_map>

class SceneMgr : public Singleton<SceneMgr> {
	friend Singleton<SceneMgr>;
public:
	enum class SceneType {
		Menu,
		GameOn,
		PlayingInstrution,
		GameOver,
		Exit,
		Edit
	};

	void add(SceneType type, Scene* scene) {
		scene_loop[type] = scene;
	}

	void set_current_scene(SceneType type) {
		scene_type = type;
		current_scene = scene_loop[type];
		current_scene->on_enter();
	}

	void switch_to(SceneType type) {
		scene_type = type;
		current_scene->on_exit();
		current_scene = scene_loop[type];
		current_scene->on_enter();
	}

	void on_update(float delta) {
		current_scene->on_update(delta);
	}

	void on_render(Camera& camera) {
		current_scene->on_render(camera);
	}
	void on_input(const SDL_Event& msg) {
		current_scene->on_input(msg);
	}

	SceneType get_scene_type() {
		return scene_type;
	}

private:
	SceneMgr() = default;
	~SceneMgr() = default;
	Scene* current_scene = nullptr;
	SceneType scene_type = SceneType::Menu;
	std::unordered_map<SceneType, Scene*> scene_loop;
};