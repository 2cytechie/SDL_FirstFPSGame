#include "game_on_scene.h"

#include "level1.h"
#include "level_mgr.h"

#include "scene_mgr.h"

GameOnScene::GameOnScene() = default;

GameOnScene::~GameOnScene() = default;

void GameOnScene::on_enter() {
	level = new Level1();
	LevelMgr::instance()->load_level(level);
	CollisionMgr::instance()->process_collide();
}

void GameOnScene::on_update(float delta) {
	LevelMgr::instance()->on_update(delta);
}

void GameOnScene::on_render(Camera& camera) {
	// ÉèÖÃÉãÏñ»ú¸úËæ
	Vector2 player_pos = LevelMgr::instance()->get_player()->get_pos();
	camera.follow_pos(player_pos);

	// ±³¾°É«
	SDL_Color bg_color{ 0,255,255,255 };
	SDL_Rect rect{
		0,0,
		1280,720
	};
	camera.fill_rect(&rect, bg_color);

	LevelMgr::instance()->on_render(camera);

	// DEBUG Åö×²Ïä
	CollisionMgr::instance()->on_debug_render(camera);
}

void GameOnScene::on_input(const SDL_Event& msg) {
	LevelMgr::instance()->on_input(msg);

	if (msg.type == SDL_KEYDOWN) {
		if (msg.key.keysym.sym == SDLK_RETURN) {
			SceneMgr::instance()->switch_to(SceneMgr::SceneType::Menu);
		}
	}
}

void GameOnScene::on_exit() {
	delete level;
	level = nullptr;
	LevelMgr::instance()->destory();
}