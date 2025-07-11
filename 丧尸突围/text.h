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

    // 移动语义支持（转移资源所有权）
    Text(Text&& other) noexcept {
        swap(*this, other);
    }

    Text& operator=(Text&& other) noexcept {
        swap(*this, other);
        return *this;
    }

    // 交换两个Text对象的资源
    friend void swap(Text& first, Text& second) noexcept {
        using std::swap;
        swap(first.text, second.text);
        swap(first.font, second.font);
        swap(first.color, second.color);
        swap(first.background_color, second.background_color);
        swap(first.position, second.position);
        swap(first.surface, second.surface);
    }

    // 设置文本内容（同时更新表面）
    void set_text(const std::string& newText) {
        if (text != newText) {
            text = newText;
            updateSurface();
        }
    }

    // 设置字体（同时更新表面）
    void set_font(TTF_Font* newFont) {
        if (font != newFont) {
            font = newFont;
            updateSurface();
        }
    }

    // 设置文本颜色（同时更新表面）
    void set_color(const SDL_Color& newColor) {
        if (!(color.r == newColor.r && color.g == newColor.g &&
            color.b == newColor.b && color.a == newColor.a)) {
            color = newColor;
            updateSurface();
        }
    }

    // 设置背景颜色（同时更新表面）
    void set_backgroundColor(const SDL_Color& bg_color) {
        if (!(background_color.r == bg_color.r && background_color.g == bg_color.g &&
            background_color.b == bg_color.b && background_color.a == bg_color.a)) {
            background_color = bg_color;
            updateSurface();
        }
    }

    // 设置位置（仅更新坐标，不影响表面）
    void set_pos(int x, int y) {
        position.x = x;
        position.y = y;
    }

    void set_pos(const SDL_Point& pos) {
        position = pos;
    }

    // 获取文本尺寸（基于表面大小）
    SDL_Point get_size() const {
        if (surface) {
            return { surface->w, surface->h };
        }
        return { 0, 0 };
    }

    // 渲染文本到渲染器
    void on_render(SDL_Renderer* renderer) {
        if (!renderer || !surface) return;

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (!texture) {
            SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Failed to create texture: %s", SDL_GetError());
            return;
        }

        // 渲染目标矩形（位置+尺寸）
        SDL_Rect dest_rect = {
            position.x - surface->w / 2,
            position.y - surface->h / 2,
            surface->w,
            surface->h
        };

        SDL_RenderCopy(renderer, texture, nullptr, &dest_rect);
    }

private:
    std::string text;                               // 文本内容
    TTF_Font* font = nullptr;                       // 字体（外部管理生命周期）
    SDL_Color color;                                // 文本颜色
    SDL_Color background_color;                     // 背景颜色
    SDL_Point position;                             // 渲染位置（居中）
    SDL_Surface* surface = nullptr;                 // 文本表面（用于生成纹理）

    // 释放表面资源
    void freeSurface() {
        if (surface) {
            SDL_FreeSurface(surface);
            surface = nullptr;
        }
    }

    // 更新表面（文本/字体/颜色变化时调用）
    void updateSurface() {
        freeSurface();

        if (!font || text.empty()) return;

        if (background_color.a == 0) {
            // 透明背景（抗锯齿，高质量）
            surface = TTF_RenderUTF8_Blended(font, text.c_str(), color);
        }
        else {
            // 不透明背景（快速渲染）
            surface = TTF_RenderUTF8_Shaded(font, text.c_str(), color, background_color);
        }

        // 错误处理
        if (!surface) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to render text: %s", TTF_GetError());
        }
    }
};