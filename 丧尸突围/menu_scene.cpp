#include "menu_scene.h"
#include "scene_mgr.h"
#include "name.h"
#include "res_mgr.h"

MenuScene::MenuScene() = default;

MenuScene::~MenuScene() = default;

void MenuScene::on_enter() {
	select_player = 0;

	font = TTF_OpenFont("resources/IPix.ttf", 30);
	start_game			=	Text(u8"开始游戏", font, { window_size.x / 4,window_size.y / 10 * 5 });		// 开始游戏
	playing_instrution	=	Text(u8"游戏玩法", font, { window_size.x / 4,window_size.y / 10 * 6 });		// 游戏玩法
	exit_game			=	Text(u8"退出游戏", font, { window_size.x / 4,window_size.y / 10 * 7 });		// 退出游戏

	update();
}

void MenuScene::on_update(float delta) {
	animation_player->on_update(delta);
}

void MenuScene::on_render(Camera& camera) {
	// 背景
	camera.set_color(135, 206, 235, 255);
	SDL_Rect rect{ 0,0,1280,720 };
	camera.fill_rect(&rect);

	// 选择框
	camera.set_color(10, 10, 255, 255);
	Vector2 size{ 260,50 };
	SDL_Rect dst{ window_size.x / 4 - size.x / 2, window_size.y / 10 * (5 + select_game) - size.y / 2,size.x,size.y };
	camera.draw_rect(&dst);

	camera.draw_text(&start_game);
	camera.draw_text(&playing_instrution);
	camera.draw_text(&exit_game);
	camera.draw_text(&player_name);

	animation_player->on_render(camera);
	
}
void MenuScene::on_input(const SDL_Event& msg) {
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
		case SDLK_LEFT:
		case SDLK_a:
			select_player = select_player <= 0 ? PlayerName.size() - 1 : select_player - 1;
			update();
			break;
		case SDLK_RIGHT:
		case SDLK_d:
			select_player = select_player >= PlayerName.size() - 1 ? 0 : select_player + 1;
			update();
			break;
		case SDLK_KP_ENTER:
		case SDLK_RETURN:
		{
			if (select_game == 0) {
				SceneMgr::instance()->switch_to(SceneMgr::SceneType::GameOn);
			}
			else if (select_game == 1) {
				SceneMgr::instance()->switch_to(SceneMgr::SceneType::PlayingInstrution);
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
void MenuScene::on_exit() {
	TTF_CloseFont(font);
	font = nullptr;
}

void MenuScene::update() {
	std::string select_player_name = PlayerName[select_player];
	animation_player = ResMgr::instance()->find_animation(select_player_name + "_Idle");
	animation_player->set_pos(window_size.x / 4 * 3, window_size.y / 10 * 7);
	animation_player->set_size(5);
	player_name = Text(select_player_name, font, { window_size.x / 4 * 3 ,window_size.y / 10 * 7 + 20 });	// 角色名字
}
