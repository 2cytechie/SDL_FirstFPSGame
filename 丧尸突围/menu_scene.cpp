#include "menu_scene.h"
#include "scene_mgr.h"
#include "character_name.h"
#include "res_mgr.h"
#include "level_mgr.h"
#include "player_ins.h"

MenuScene::MenuScene() = default;

MenuScene::~MenuScene() = default;

void MenuScene::on_enter() {
	select_game = 0;

	font = TTF_OpenFont("resources/IPix.ttf", 30);
	start_game.set(u8"开始游戏", font, { window_size.x / 4,window_size.y / 10 * 5 });				// 开始游戏
	playing_instrution.set(u8"游戏玩法", font, { window_size.x / 4,window_size.y / 10 * 6 });		// 游戏玩法
	exit_game.set(u8"退出游戏", font, { window_size.x / 4,window_size.y / 10 * 7 });				// 退出游戏

	update();
}

void MenuScene::on_update(float delta) {
	animation_player->on_update(delta);
}

void MenuScene::on_render(Camera& camera) {
	// 背景
	SDL_Color bg_color{ 135, 206, 235, 255 };
	SDL_Rect rect{ 0,0,1280,720 };
	camera.fill_rect(&rect, bg_color);

	// 选择框
	SDL_Color select_color{ 10, 10, 255, 255 };
	Vector2 size{ 260,50 };
	SDL_Rect dst{ window_size.x / 4 - size.x / 2, window_size.y / 10 * (5 + select_game) - size.y / 2,size.x,size.y };
	camera.draw_rect(&dst, select_color);

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
				Player* player = nullptr;
				switch (select_player) {
				case 0:
					player = new Sprites();
					break;
				case 1:
					player = new Pexel();
					break;
				case 2:
					player = new Knight();
					break;
				case 3:
					player = new Soldier();
					break;
				case 4:
					player = new Fighter();
					break;
				case 5:
					player = new Samurai();
					break;
				case 6:
					player = new Martial();
					break;

				default:
					SDL_Log("Creat player Error !!!");
				}
				LevelMgr::instance()->set_player(player);
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
	Vector2 animation_size = animation_player->get_frame_size();
	animation_player->set_size(200 / animation_size.y);
	player_name.set(select_player_name, font, { window_size.x / 4 * 3 ,window_size.y / 10 * 7 + 20 });	// 角色名字
}
