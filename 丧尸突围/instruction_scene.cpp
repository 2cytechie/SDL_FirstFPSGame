#include "instruction_scene.h"
#include "scene_mgr.h"
#include "res_mgr.h"
#include "character_name.h"

InstructionScene::InstructionScene() = default;

InstructionScene::~InstructionScene() = default;

void InstructionScene::on_enter() {
	font_max = TTF_OpenFont("resources/IPix.ttf", 40);
	font = TTF_OpenFont("resources/IPix.ttf", 30);
	font_min = TTF_OpenFont("resources/IPix.ttf", 20);
	instructions.push_back(Text(u8"游戏玩法:", font_max, { window_size.x / 16, window_size.y / 16 * 4 }, Text::TextType::Left));
	instructions.push_back(Text(u8"  移动:    W  A  S  D  上下左右移动", font, { window_size.x / 16,window_size.y / 16 * 6 }, Text::TextType::Left));
	instructions.push_back(Text(u8"  攻击:    鼠标左键", font, { window_size.x / 16,window_size.y / 16 * 7 }, Text::TextType::Left));

	instructions.push_back(Text(u8"Enter  返回菜单界面", font, { window_size.x / 2,window_size.y / 16 * 12 }, Text::TextType::Right, { 200,20,20,255 }));

	instructions.push_back(Text(u8"制作人名单:", font, { window_size.x / 16,window_size.y / 16 * 13 }, Text::TextType::Left));
	instructions.push_back(Text(u8"2cytechie", font_min, { window_size.x / 16,window_size.y / 16 * 14 }, Text::TextType::Left));
	instructions.push_back(Text(u8"github:  https://github.com/2cytechie/SDL_FirstFPSGame", font_min, { window_size.x / 16,window_size.y / 16 * 15 }, Text::TextType::Left));
	
	update();
}
void InstructionScene::on_update(float delta) {
	attack_animation->on_update(delta);
}
void InstructionScene::on_render(Camera& camera) {
    camera.reset();
	// 背景
	SDL_Color bg_color{ 135, 206, 235, 255 };
	SDL_Rect rect{ 0,0,1280,720 };
	camera.fill_rect(&rect, bg_color);

	for (auto& ins : instructions) {
		camera.draw_text(&ins);
	}
	attack_animation->on_render(camera);
	camera.draw_text(&player_name);
}
void InstructionScene::on_input(const SDL_Event& msg) {
	if (msg.type == SDL_KEYDOWN) {
		switch (msg.key.keysym.sym) {
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
		case SDLK_RETURN:
		case SDLK_KP_ENTER:
			SceneMgr::instance()->switch_to(SceneMgr::SceneType::Menu);
			return;
		}
	}
}
void InstructionScene::on_exit() {
	instructions.clear();
	TTF_CloseFont(font_min);
	TTF_CloseFont(font);
	TTF_CloseFont(font_max);
}

void InstructionScene::update() {
	std::string attack_player_name = PlayerName[select_player];
	attack_animation = ResMgr::instance()->find_animation(attack_player_name + "_Attack");
	attack_animation->set_pos(window_size.x / 4 * 3, window_size.y / 10 * 7);
	attack_animation->set_size(5);
	player_name.set(attack_player_name, font, { window_size.x / 4 * 3 ,window_size.y / 10 * 7 + 20 });
}