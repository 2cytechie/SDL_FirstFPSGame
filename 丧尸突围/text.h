#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <algorithm>

class Text {
public:
    enum class TextType {
        Left,
        Center,
        Right
    };

    Text() = default;

    Text(const std::string& text, TTF_Font* font,
        const SDL_Point pos = { 0, 0 },
        const TextType type = TextType::Center,
        const SDL_Color color = { 0, 0, 0, 255 },
        const SDL_Color bg_color = { 0, 0, 0, 0 })
        : text(text), font(font), position(pos), type(type), color(color), background_color(bg_color) {}

    ~Text() {
        SDL_DestroyTexture(texture);
    }

public:
    std::string text;
    TextType type = TextType::Center;
    TTF_Font* font = nullptr;
    SDL_Color color;
    SDL_Color background_color;
    SDL_Point position;
    SDL_Point size{ 0,0 };
    SDL_Texture* texture = nullptr;

};