#include "res_mgr.h"
#include <SDL_image.h>
#include <string>
#include <filesystem>

ResMgr* ResMgr::manager = nullptr;

ResMgr* ResMgr::instance()
{
    if (!manager)
        manager = new ResMgr();

    return manager;
}

Mix_Chunk* ResMgr::find_audio(const std::string& name)
{
    return audio_pool[name];
}

Animation* ResMgr::find_animation(const std::string& name)
{
    return animation_pool[name];
}

ResMgr::ResMgr() = default;

ResMgr::~ResMgr() = default;

void ResMgr::load(SDL_Renderer* renderer)
{
    using namespace std::filesystem;

    for (const auto& entry : directory_iterator("resources")) {
        // resources 文件夹下的文件夹
        if (entry.is_directory()) {
            for (const auto& file : directory_iterator(entry.path())) {
                // 文件里的文件是一个普通文件
                if (file.is_regular_file()) {
                    const path& file_path = file.path();
                    if (file_path.extension() == ".png") {
                        std::string file_name = file_path.stem().string();

                        // 查找 @ 符号的位置
                        size_t at_pos = file_name.find('@');
                        if (at_pos != std::string::npos && at_pos < file_name.length() - 1) {
                            // 提取 @ 符号  前面作为key  后面的部分作为帧数
                            std::string key = file_name.substr(0, at_pos);
                            int animation_frame = std::stoi(file_name.substr(at_pos + 1));

                            SDL_Texture* texture = IMG_LoadTexture(renderer, file_path.u8string().c_str());
                            Animation* animation = new Animation();
                            animation->load(texture, animation_frame);
                            animation_pool[key] = animation;
                        }
                    }
                    else if (file_path.extension() == ".gif") {
                        IMG_Animation* animation_JPG = IMG_LoadAnimation(file_path.u8string().c_str());
                        Animation* animation = new Animation();
                        animation->load(animation_JPG);
                        animation_pool[file_path.stem().u8string()] = animation;
                    }
                    else if (file_path.extension() == ".mp3")
                    {
                        Mix_Chunk* audio = Mix_LoadWAV(file_path.u8string().c_str());
                        audio_pool[file_path.stem().u8string()] = audio;
                    }

                }
            }
        }
    }
}