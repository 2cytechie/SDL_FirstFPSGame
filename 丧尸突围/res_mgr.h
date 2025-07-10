#pragma once

#include <SDL.h>
#include <SDL_mixer.h>

#include <string>
#include <unordered_map>

#include "animation.h"

class ResMgr
{
public:
    static ResMgr* instance();

    void load(SDL_Renderer* renderer);
    Mix_Chunk* find_audio(const std::string& name);
    Animation* find_animation(const std::string& name);

private:
    ResMgr();
    ~ResMgr();

private:
    static ResMgr* manager;
    std::unordered_map<std::string, Mix_Chunk*> audio_pool;
    std::unordered_map<std::string, Animation*> animation_pool;
};