#include "game_over_scene.h"
#include "scene_mgr.h"
#include "res_mgr.h"

GameOverScene::GameOverScene() = default;

GameOverScene::~GameOverScene() = default;

void GameOverScene::on_enter() {
	TTF_Font* font_max = TTF_OpenFont("resources/IPix.ttf", 100);
	TTF_Font* font = TTF_OpenFont("resources/IPix.ttf", 30);
	game_over			= Text(u8"游戏结束", font_max, { window_size.x / 2,window_size.y / 10 * 3 });	// 游戏结束
	restart				= Text(u8"重新开始", font, { window_size.x / 2,window_size.y / 10 * 5 });		// 重新开始
	menu				= Text(u8"游戏菜单", font, { window_size.x / 2,window_size.y / 10 * 6 });		// 游戏菜单
	exit_game			= Text(u8"退出游戏", font, { window_size.x / 2,window_size.y / 10 * 7 });		// 退出游戏
	
	TTF_CloseFont(font);
	TTF_CloseFont(font_max);
}
void GameOverScene::on_update(float delta) {

}
void GameOverScene::on_render(SDL_Renderer* renderer) {
	// 背景
	SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);
	SDL_Rect rect{ 0,0,1280,720 };
	SDL_RenderFillRect(renderer, &rect);

	// 选择框
	SDL_SetRenderDrawColor(renderer, 10, 10, 255, 255);
	Vector2 size{ 260,50 };
	SDL_Rect dst{ window_size.x / 2 - size.x / 2, window_size.y / 10 * (5 + select_game) - size.y / 2,size.x,size.y };
	SDL_RenderDrawRect(renderer, &dst);

	game_over.on_render(renderer);
	restart.on_render(renderer);
	menu.on_render(renderer);
	exit_game.on_render(renderer);

}
void GameOverScene::on_input(const SDL_Event& msg) {
	if (msg.type == SDL_KEYDOWN) {
		switch (msg.key.keysym.sym) {
		case SDLK_UP:
		case SDLK_w:
			select_game = select_game <= 0 ? 0 : select_game - 1;
			break;
		case SDLK_DOWN:
		case SDLK_s:
			select_game = select_game >= 2 ? 2 : select_game + 1;
			break;
		case SDLK_KP_ENTER:
		case SDLK_RETURN:
		{
			if (select_game == 0) {
				SceneMgr::instance()->switch_to(SceneMgr::SceneType::GameOn);
			}
			else if (select_game == 1) {
				SceneMgr::instance()->switch_to(SceneMgr::SceneType::Menu);
			}
			else if (select_game == 2) {
				Mix_PlayChannel(-1, ResMgr::instance()->find_audio("ui_confirm"), 0);
				SceneMgr::instance()->switch_to(SceneMgr::SceneType::Exit);
			}
			return;
		}

		}

		Mix_PlayChannel(-1, ResMgr::instance()->find_audio("ui_switch"), 0);
	}
}
void GameOverScene::on_exit() {

}