#include "instruction_scene.h"
#include "scene_mgr.h"
#include "res_mgr.h"
#include "name.h"

InstructionScene::InstructionScene() = default;

InstructionScene::~InstructionScene() = default;

void InstructionScene::on_enter() {
	instructions.clear();

	TTF_Font* font_max = TTF_OpenFont("resources/IPix.ttf", 40);
	TTF_Font* font = TTF_OpenFont("resources/IPix.ttf", 30);
	TTF_Font* font_min = TTF_OpenFont("resources/IPix.ttf", 20);
	instructions.push_back(Text(u8"游戏玩法:", font_max, { window_size.x / 16, window_size.y / 16 * 4 }, Text::TextType::Left));
	instructions.push_back(Text(u8"  移动:    W  A  S  D  上下左右移动", font, { window_size.x / 16,window_size.y / 16 * 6 }, Text::TextType::Left));
	instructions.push_back(Text(u8"  攻击:    鼠标左键", font, { window_size.x / 16,window_size.y / 16 * 7 }, Text::TextType::Left));

	instructions.push_back(Text(u8"Enter  返回菜单界面", font, { window_size.x / 2,window_size.y / 16 * 11 }, Text::TextType::Right));

	instructions.push_back(Text(u8"制作人名单:", font, { window_size.x / 16,window_size.y / 16 * 13 }, Text::TextType::Left));
	instructions.push_back(Text(u8"2cytechie", font_min, { window_size.x / 16,window_size.y / 16 * 14 }, Text::TextType::Left));
	instructions.push_back(Text(u8"github:  https://github.com/2cytechie/SDL_FirstFPSGame", font_min, { window_size.x / 16,window_size.y / 16 * 15 }, Text::TextType::Left));

	std::string attack_player_name = PlayerName[select_player];
	attack_animation = ResMgr::instance()->find_animation(attack_player_name + "_Attack");
	attack_animation->set_pos(window_size.x / 4 * 3, window_size.y / 10 * 7);
	attack_animation->set_size(5);
	instructions.push_back(Text(attack_player_name, font, { window_size.x / 4 * 3 ,window_size.y / 10 * 7 + 20 }, Text::TextType::Left));

	TTF_CloseFont(font_min);
	TTF_CloseFont(font);
	TTF_CloseFont(font_max);
}
void InstructionScene::on_update(float delta) {
	attack_animation->on_update(delta);
}
void InstructionScene::on_render(SDL_Renderer* renderer) {
	// 背景
	SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);
	SDL_Rect rect{ 0,0,1280,720 };
	SDL_RenderFillRect(renderer, &rect);

	for (auto& ins : instructions) {
		ins.on_render(renderer);
	}
	attack_animation->on_render(renderer);
}
void InstructionScene::on_input(const SDL_Event& msg) {
	if (msg.type == SDL_KEYDOWN) {
		switch (msg.key.keysym.sym) {
		case SDLK_LEFT:
		case SDLK_a:
			select_player = select_player <= 0 ? PlayerName.size() - 1 : select_player - 1;
			on_enter();
			break;
		case SDLK_RIGHT:
		case SDLK_d:
			select_player = select_player >= PlayerName.size() - 1 ? 0 : select_player + 1;
			on_enter();
			break;
		case SDLK_RETURN:
		case SDLK_KP_ENTER:
			SceneMgr::instance()->switch_to(SceneMgr::SceneType::Menu);
			return;
		}
	}
}
void InstructionScene::on_exit() {
	instructions.clear();
}