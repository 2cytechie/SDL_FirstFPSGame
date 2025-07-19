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
	// ����
	void shake(float strength, float duration);
	// �����
	void follow_pos(Vector2 target_pos);
	// ���ƾ���
	void fill_rect(const SDL_Rect* rect, SDL_Color color);
	// ���ƾ��ο�
	void draw_rect(const SDL_FRect* rect, SDL_Color color);
	void draw_rect(const SDL_Rect* rect, SDL_Color color);
	// �����ı�
	void draw_text(Text* text);
	void render_texture(SDL_Texture* texture, const SDL_Rect* rect_src, const SDL_FRect* rect_dst, 
		double angle, const SDL_FPoint* center, SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE) const;


public:
	Vector2 window_size{ 1280,70 };		// ���ڴ�С
	//const float damping = 0.1f;			// ����ϵ��������ƽ���ȺͲ���Ч��
	//Vector2 velocity;					// ��������ƶ��ٶȣ���̬�����Ա���״̬

	SDL_Renderer* renderer;				// 
	Timer timer_shake;					// ���ڶ���
	bool is_shaking = false;			// �����Ƿ��ڶ���
	Vector2 pos;						// �����λ��
	float shaking_strength = 0;			// �������ȴ�С

};

