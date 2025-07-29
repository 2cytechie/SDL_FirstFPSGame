#include "game_on_scene.h"
#include "level_mgr.h"

#include "scene_mgr.h"

GameOnScene::GameOnScene() = default;

GameOnScene::~GameOnScene() = default;

void GameOnScene::on_enter() {
	LevelMgr::instance()->load_level(1);
}

void GameOnScene::on_update(float delta) {
	LevelMgr::instance()->on_update(delta);
	// ÆôÓÃÅö×²Ïä
	CollisionMgr::instance()->process_collide();
}

void GameOnScene::on_render(Camera& camera) {
	// ÉèÖÃÉãÏñ»ú¸úËæ
	Vector2 player_pos = LevelMgr::instance()->get_player()->get_pos();
	camera.follow_pos(player_pos);

	// ±³¾°
	SDL_Color bg_color{ 0,255,255,255 };
	SDL_Rect rect{
		0,0,
		1280,720
	};
	camera.fill_rect(&rect, bg_color);

	LevelMgr::instance()->on_render(camera);

	// DEBUG Åö×²Ïä
	CollisionMgr::instance()->on_debug_render(camera);

	// UI
	// »æÖÆÑªÌõ
	SDL_Color color_rect = { 128,0,0,255 };
	SDL_Color color_hp = { 200,0,0,255 };

	int max_hp = LevelMgr::instance()->get_player()->get_max_hp();
    int hp = LevelMgr::instance()->get_player()->get_hp();
	Vector2 window_size = camera.get_window_size();
	Vector2 camera_pos = camera.get_pos();
	SDL_Rect rect_rect = {
		camera_pos.x + 10,
		camera_pos.y + window_size.y - 20,
		window_size.x / 3 * 2,
		10
	};
	SDL_Rect rect_hp = {
		camera_pos.x + 10,
		camera_pos.y + window_size.y - 20,
		hp / max_hp * window_size.x / 3 * 2,
		10
	};
	camera.draw_rect(&rect_rect, color_rect);
	camera.fill_rect(&rect_hp, color_hp);

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
	LevelMgr::instance()->destory();
}