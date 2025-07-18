#include "game_on_scene.h"

#include "level1.h"
#include "level_mgr.h"

GameOnScene::GameOnScene() = default;

GameOnScene::~GameOnScene() = default;

void GameOnScene::on_enter() {
	//Level1 level_1 = Level1();
	CollisionMgr::instance()->process_collide();
}

void GameOnScene::on_update(float delta) {
	LevelMgr::instance()->on_update(delta);
}

void GameOnScene::on_render(Camera& camera) {
	SDL_Color bg_color{ 0,0,255,255 };
	SDL_Rect rect{
		0,0,
		1280,720
	};
	camera.fill_rect(&rect, bg_color);

	LevelMgr::instance()->on_render(camera);
	CollisionMgr::instance()->on_debug_render(camera);
}

void GameOnScene::on_input(const SDL_Event& msg) {
	LevelMgr::instance()->on_input(msg);
}

void GameOnScene::on_exit() {
	LevelMgr::instance()->destory();
}