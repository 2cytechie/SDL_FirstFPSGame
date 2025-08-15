#include "game_on_scene.h"
#include "level_mgr.h"

#include "scene_mgr.h"

GameOnScene::GameOnScene() = default;

GameOnScene::~GameOnScene() = default;

void GameOnScene::on_enter() {
	LevelMgr::instance()->load_level(level_num);
}

void GameOnScene::on_update(float delta) {
	LevelMgr::instance()->on_update(delta);
	// ÆôÓÃÅö×²Ïä
	CollisionMgr::instance()->process_collide();

	if (LevelMgr::instance()->check_win()) {
		level_num++;
		SceneMgr::instance()->switch_to(SceneMgr::SceneType::GameOn);
		if (DEBUG) {
			SDL_Log("Next level");
		}
	}
}

void GameOnScene::on_render(Camera& camera) {
	LevelMgr::instance()->on_render(camera);

	// DEBUG Åö×²Ïä
	if (DEBUG) {
		CollisionMgr::instance()->on_debug_render(camera);
	}
}

void GameOnScene::on_input(const SDL_Event& msg) {
	LevelMgr::instance()->on_input(msg);

	//if (msg.type == SDL_KEYDOWN) {
	//	if (msg.key.keysym.sym == SDLK_RETURN) {
	//		SceneMgr::instance()->switch_to(SceneMgr::SceneType::Menu);
	//	}
	//}
}

void GameOnScene::on_exit() {
	LevelMgr::instance()->destory();
}