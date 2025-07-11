#include "menu_scene.h"
#include "name.h"
#include "res_mgr.h"

MenuScene::MenuScene() = default;

MenuScene::~MenuScene() = default;

void MenuScene::on_enter() {
	TTF_Font* font = TTF_OpenFont("resources/IPix.ttf", 30);
	resume_game			=	Text(u8"继续游戏", font, { window_size.x / 4,window_size.y / 10 * 5 });		// 继续游戏
	start_game			=	Text(u8"开始游戏", font, { window_size.x / 4,window_size.y / 10 * 6 });		// 开始游戏
	playing_instrution	=	Text(u8"游戏玩法", font, { window_size.x / 4,window_size.y / 10 * 7 });		// 游戏玩法
	exit_game			=	Text(u8"退出游戏", font, { window_size.x / 4,window_size.y / 10 * 8 });		// 退出游戏

	update();
}

void MenuScene::on_update(Camera& camera, float delta) {
	camera.on_undate(delta);
	
	animation_player->on_update(delta);
}
void MenuScene::on_render(SDL_Renderer* renderer, Camera& camera) {
	// 背景
	SDL_SetRenderDrawColor(renderer,128,128,128,255 );
	SDL_Rect rect{ 0,0,1280,720 };
	SDL_RenderFillRect(renderer, &rect);

	// 选择框
	SDL_SetRenderDrawColor(renderer, 10, 10, 255, 255);
	Vector2 size{ 260,50 };
	SDL_Rect dst{ window_size.x / 4 - size.x / 2, window_size.y / 10 * (5 + select_game) - size.y / 2,size.x,size.y };
	SDL_RenderDrawRect(renderer, &dst);

	resume_game.on_render(renderer);
	start_game.on_render(renderer);
	playing_instrution.on_render(renderer);
	exit_game.on_render(renderer);
	player_name.on_render(renderer);

	animation_player->on_render(renderer);
	
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
			select_game = select_game >= 3 ? 3 : select_game + 1;
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
		}
	}
}
void MenuScene::on_exit() {
	
}

void MenuScene::update() {
	TTF_Font* font = TTF_OpenFont("resources/IPix.ttf", 30);
	std::string select_player_name = PlayerName[select_player];
	animation_player = ResMgr::instance()->find_animation(select_player_name + "_Idle");
	animation_player->set_pos(window_size.x / 4 * 3, window_size.y / 4 * 3);
	animation_player->set_size(5);
	player_name = Text(select_player_name, font, { window_size.x / 4 * 3 ,window_size.y / 4 * 3 + 20 });	// 角色名字
}