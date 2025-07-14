#pragma once

#include "timer.h"
#include "text.h"
#include "vector2.h"

#include<SDL.h>

class Camera {
public:
	Camera(SDL_Renderer* renderer);

	~Camera();

	const Vector2& get_pos()const {
		return pos;
	}

	void reset() {
		pos.x = 0;
		pos.y = 0;
	}

	void on_update(float delta);
	void shake(float strength, float duration);
	void set_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void fill_rect(const SDL_Rect* rect);
	void draw_rect(const SDL_Rect* rect);
	void draw_text(Text* text);
	void render_texture(SDL_Texture* texture, const SDL_Rect* rect_src, const SDL_Rect* rect_dst, 
		double angle, const SDL_Point* center, SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE) const;


public:
	SDL_Renderer* renderer;				// 
	Timer timer_shake;					// 窗口抖动
	bool is_shaking = false;			// 窗口是否在抖动
	Vector2 pos;						// 摄像机位置
	float shaking_strength = 0;			// 抖动幅度大小

};

