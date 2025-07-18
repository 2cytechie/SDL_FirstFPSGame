#define SDL_MAIN_HANDLED

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <chrono>
#include <thread>

#include "vector2.h"
#include "res_mgr.h"
#include "camera.h"
#include "animation.h"
#include "scene_mgr.h"
#include "menu_scene.h"
#include "game_on_scene.h"
#include "instruction_scene.h"
#include "game_over_scene.h"
#include "exit_scene.h"


bool DEBUG = true;


void scene_init() {
    SceneMgr::instance()->add(SceneMgr::SceneType::Menu, new MenuScene());
    SceneMgr::instance()->add(SceneMgr::SceneType::GameOn, new GameOnScene());
    SceneMgr::instance()->add(SceneMgr::SceneType::PlayingInstrution, new InstructionScene());
    SceneMgr::instance()->add(SceneMgr::SceneType::GameOver, new GameOverScene());
    SceneMgr::instance()->add(SceneMgr::SceneType::Exit, new ExitScene());

    SceneMgr::instance()->set_current_scene(SceneMgr::SceneType::Menu);
}

int main(int argc, char** argv)
{
    using namespace std::chrono;

    // 初始化
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    Mix_Init(MIX_INIT_MP3);
    TTF_Init();

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    SDL_Window* window = SDL_CreateWindow(u8"《丧尸突围》",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1280, 720, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // 隐藏光标
    //SDL_ShowCursor(SDL_DISABLE);
    // 禁用输入法
    SDL_StopTextInput();

    // 加载数据
    ResMgr::instance()->load(renderer);
    scene_init();
    
    Camera* camera = new Camera(renderer);
    SDL_Event event;
    bool is_quit = false;

    // 播放背景音乐
    Mix_PlayChannel(-1, ResMgr::instance()->find_audio("bgm"), -1);

    const nanoseconds frame_duration(100000000 / 144);
    steady_clock::time_point last_tick = steady_clock::now();

    while (!is_quit)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                is_quit = true;
                break;
            }
            is_quit = SceneMgr::instance()->get_scene_type() == SceneMgr::SceneType::Exit;
            SceneMgr::instance()->on_input(event);
        }
        steady_clock::time_point frame_start = steady_clock::now();
        duration<float> delta = duration<float>(frame_start - last_tick);
          
        // 更新游戏数据
        SceneMgr::instance()->on_update(delta.count());

        // 清除上一次数据并渲染
        SDL_RenderClear(renderer);
        SceneMgr::instance()->on_render(*camera);
        SDL_RenderPresent(renderer);

        last_tick = frame_start;
        nanoseconds sleep_duration = frame_duration - (steady_clock::now() - frame_start);
        if (sleep_duration > nanoseconds(0))
            std::this_thread::sleep_for(sleep_duration);
    }

    // 释放资源
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}