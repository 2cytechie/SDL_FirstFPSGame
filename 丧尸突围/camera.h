#pragma once

#include "timer.h"
#include "text.h"
#include "vector2.h"

#include<SDL.h>

class Camera {
public:
	Camera(SDL_Renderer* renderer);

	~Camera();

	void set_pos(Vector2 pos) {
		this->pos = pos;
	}

	const Vector2& get_pos()const {
		return pos;
	}

	void reset() {
		pos.x = 0;
		pos.y = 0;
	}

	const Vector2& get_window_size()const {
		return window_size;
	}

	void on_update(float delta);
	// 抖动
	void shake(float strength, float duration);
	// 跟随点
	void follow_pos(Vector2 target_pos);
	// 绘制矩形
	void fill_rect(const SDL_Rect* rect, SDL_Color color);
	// 绘制矩形框
	void draw_rect(const SDL_FRect* rect, SDL_Color color);
	void draw_rect(const SDL_Rect* rect, SDL_Color color);
	// 绘制文本
	void draw_text(Text* text);
	void render_texture(SDL_Texture* texture, const SDL_Rect* rect_src, const SDL_FRect* rect_dst, 
		double angle, const SDL_FPoint* center, SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE) const;


public:
	Vector2 window_size{ 1280,70 };		// 窗口大小
	//const float damping = 0.1f;			// 阻尼系数，控制平滑度和残留效果
	//Vector2 velocity;					// 摄像机的移动速度，静态变量以保持状态

	SDL_Renderer* renderer;				// 
	Timer timer_shake;					// 窗口抖动
	bool is_shaking = false;			// 窗口是否在抖动
	Vector2 pos;						// 摄像机位置
	float shaking_strength = 0;			// 抖动幅度大小

};

