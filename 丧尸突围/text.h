#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <algorithm>

class Text {
public:
    Text() = default;

    Text(const std::string& text, TTF_Font* font,
        const SDL_Point& pos = { 0, 0 },
        const SDL_Color& color = { 255, 255, 255, 255 },
        const SDL_Color& bg_color = { 0, 0, 0, 0 })
        : text(text), font(font), color(color), background_color(bg_color), position(pos) {
        updateSurface();
    }

    ~Text() {
        freeSurface();
    }

    // �ƶ�����֧�֣�ת����Դ����Ȩ��
    Text(Text&& other) noexcept {
        swap(*this, other);
    }

    Text& operator=(Text&& other) noexcept {
        swap(*this, other);
        return *this;
    }

    // ��������Text�������Դ
    friend void swap(Text& first, Text& second) noexcept {
        using std::swap;
        swap(first.text, second.text);
        swap(first.font, second.font);
        swap(first.color, second.color);
        swap(first.background_color, second.background_color);
        swap(first.position, second.position);
        swap(first.surface, second.surface);
    }

    // �����ı����ݣ�ͬʱ���±��棩
    void set_text(const std::string& newText) {
        if (text != newText) {
            text = newText;
            updateSurface();
        }
    }

    // �������壨ͬʱ���±��棩
    void set_font(TTF_Font* newFont) {
        if (font != newFont) {
            font = newFont;
            updateSurface();
        }
    }

    // �����ı���ɫ��ͬʱ���±��棩
    void set_color(const SDL_Color& newColor) {
        if (!(color.r == newColor.r && color.g == newColor.g &&
            color.b == newColor.b && color.a == newColor.a)) {
            color = newColor;
            updateSurface();
        }
    }

    // ���ñ�����ɫ��ͬʱ���±��棩
    void set_backgroundColor(const SDL_Color& bg_color) {
        if (!(background_color.r == bg_color.r && background_color.g == bg_color.g &&
            background_color.b == bg_color.b && background_color.a == bg_color.a)) {
            background_color = bg_color;
            updateSurface();
        }
    }

    // ����λ�ã����������꣬��Ӱ����棩
    void set_pos(int x, int y) {
        position.x = x;
        position.y = y;
    }

    void set_pos(const SDL_Point& pos) {
        position = pos;
    }

    // ��ȡ�ı��ߴ磨���ڱ����С��
    SDL_Point get_size() const {
        if (surface) {
            return { surface->w, surface->h };
        }
        return { 0, 0 };
    }

    // ��Ⱦ�ı�����Ⱦ��
    void on_render(SDL_Renderer* renderer) {
        if (!renderer || !surface) return;

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (!texture) {
            SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Failed to create texture: %s", SDL_GetError());
            return;
        }

        // ��ȾĿ����Σ�λ��+�ߴ磩
        SDL_Rect dest_rect = {
            position.x - surface->w / 2,
            position.y - surface->h / 2,
            surface->w,
            surface->h
        };

        SDL_RenderCopy(renderer, texture, nullptr, &dest_rect);
    }

private:
    std::string text;                               // �ı�����
    TTF_Font* font = nullptr;                       // ���壨�ⲿ�����������ڣ�
    SDL_Color color;                                // �ı���ɫ
    SDL_Color background_color;                     // ������ɫ
    SDL_Point position;                             // ��Ⱦλ�ã����У�
    SDL_Surface* surface = nullptr;                 // �ı����棨������������

    // �ͷű�����Դ
    void freeSurface() {
        if (surface) {
            SDL_FreeSurface(surface);
            surface = nullptr;
        }
    }

    // ���±��棨�ı�/����/��ɫ�仯ʱ���ã�
    void updateSurface() {
        freeSurface();

        if (!font || text.empty()) return;

        if (background_color.a == 0) {
            // ͸������������ݣ���������
            surface = TTF_RenderUTF8_Blended(font, text.c_str(), color);
        }
        else {
            // ��͸��������������Ⱦ��
            surface = TTF_RenderUTF8_Shaded(font, text.c_str(), color, background_color);
        }

        // ������
        if (!surface) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to render text: %s", TTF_GetError());
        }
    }
};