#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

#include "vector2.h"

class Text {
public:
    enum class TextType {
        Left,
        Center,
        Right
    };

    Text() = default;

    Text(const std::string& text, TTF_Font* font,
        const Vector2 pos = { 0, 0 },
        const TextType type = TextType::Center,
        const SDL_Color color = { 0, 0, 0, 255 },
        const SDL_Color bg_color = { 0, 0, 0, 0 })
        : text(text), font(font), position(pos), type(type), color(color), background_color(bg_color) {}

    ~Text() {
        SDL_DestroyTexture(texture);
    }

    void set(const std::string& text, TTF_Font* font,
        const Vector2 pos = { 0, 0 },
        const TextType type = TextType::Center,
        const SDL_Color color = { 0, 0, 0, 255 },
        const SDL_Color bg_color = { 0, 0, 0, 0 }) {
        this->text = text;
        this->font = font;
        this->position = pos;
        this->type = type;
        this->color = color;
        this->background_color = bg_color;

        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

public:
    std::string text;
    TextType type = TextType::Center;
    TTF_Font* font = nullptr;
    SDL_Color color{ 0, 0, 0, 255 };
    SDL_Color background_color{ 0, 0, 0, 0 };
    Vector2 position;
    Vector2 size{ 0,0 };
    SDL_Texture* texture = nullptr;

};