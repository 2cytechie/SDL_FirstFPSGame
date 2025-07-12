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
        : text(text), font(font), position(pos), type(type), color(color), background_color(bg_color) {
        updateResources();
    }

    ~Text() {
        freeResources();
    }

    // �ƶ�����֧��
    Text(Text&& other) noexcept {
        swap(*this, other);
    }

    Text& operator=(Text&& other) noexcept {
        swap(*this, other);
        return *this;
    }

    friend void swap(Text& first, Text& second) noexcept {
        using std::swap;
        // �������г�Ա���������������ͱ��棩
        swap(first.text, second.text);
        swap(first.font, second.font);
        swap(first.type, second.type);
        swap(first.color, second.color);
        swap(first.background_color, second.background_color);
        swap(first.position, second.position);
        swap(first.surface, second.surface);
        swap(first.texture, second.texture);
    }

    // ������ʾ��ʽ
    void set_type(TextType type) {
        this->type = type;
    }

    // �����ı����ݣ�������Դ���£�
    void set_text(const std::string& newText) {
        if (text != newText) {
            text = newText;
            updateResources();
        }
    }

    // �������壨������Դ���£�
    void set_font(TTF_Font* newFont) {
        if (font != newFont) {
            font = newFont;
            updateResources();
        }
    }

    // �����ı���ɫ
    void set_color(const SDL_Color& newColor) {
        if (!(color.r == newColor.r && color.g == newColor.g &&
            color.b == newColor.b && color.a == newColor.a)) {
            color = newColor;
            updateResources();
        }
    }

    // ���ñ�����ɫ
    void set_backgroundColor(const SDL_Color& bg_color) {
        if (!(background_color.r == bg_color.r && background_color.g == bg_color.g &&
            background_color.b == bg_color.b && background_color.a == bg_color.a)) {
            background_color = bg_color;
            updateResources();
        }
    }

    void set_pos(int x, int y) {
        position.x = x;
        position.y = y;
    }

    void set_pos(const SDL_Point& pos) {
        position = pos;
    }

    SDL_Point get_size() const {
        if (surface) {
            return { surface->w, surface->h };
        }
        return { 0, 0 };
    }

    void on_render(SDL_Renderer* renderer) {
        if (!renderer || !surface) return;

        if (!texture) {
            createTexture(renderer);
        }

        int put_x = position.x;
        switch (type) {
        case TextType::Center:  put_x = position.x - surface->w / 2;        break;
        case TextType::Right:   put_x = position.x - surface->w;            break;
        }
        SDL_Rect dest_rect = {
            put_x,
            position.y - surface->h / 2,
            surface->w,
            surface->h
        };
        SDL_RenderCopy(renderer, texture, nullptr, &dest_rect);

    }

private:
    std::string text;
    TextType type;
    TTF_Font* font = nullptr;
    SDL_Color color;
    SDL_Color background_color;
    SDL_Point position;
    SDL_Surface* surface = nullptr;
    SDL_Texture* texture = nullptr;

    // �ͷű����������Դ
    void freeResources() {
        if (surface) {
            SDL_FreeSurface(surface);
            surface = nullptr;
        }
        if (texture) {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }
    }

    // ��������
    void createTexture(SDL_Renderer* renderer) {
        // �����پ�����
        if (texture) {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }
        // ��surface����������
        if (surface && renderer) {
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            if (!texture) {
                SDL_LogError(SDL_LOG_CATEGORY_RENDER, "������ʧ��: %s", SDL_GetError());
            }
        }
    }

    // ���±��棨�ı�/����/��ɫ�仯ʱ���ã�
    void updateResources() {
        freeResources(); // ���ͷž���Դ

        if (!font || text.empty()) return;

        // ������surface
        if (background_color.a == 0) {
            surface = TTF_RenderUTF8_Blended(font, text.c_str(), color);
        }
        else {
            surface = TTF_RenderUTF8_Shaded(font, text.c_str(), color, background_color);
        }

        if (!surface) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "���洴��ʧ��: %s", TTF_GetError());
            return;
        }

    }
};