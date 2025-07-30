#pragma once

#include "timer.h"
#include "text.h"
#include "vector2.h"

#include<SDL.h>

class Camera {
public:
	Camera(SDL_Renderer* renderer);

	~Camera();

	void set_pos(Vector2 new_pos) {
		last_pos = pos;
		pos = new_pos;
	}

	const Vector2& get_pos()const {
		return pos;
	}

	const Vector2& get_camera_move()const {
		return pos - last_pos;
	}

	void reset() {
		pos.x = 0;
		pos.y = 0;
	}

	void set_window_size(Vector2 size) {
		window_size = size;
	}

	const Vector2& get_window_size()const {
		return window_size;
	}

	void on_update(float delta);
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
	Vector2 window_size{ 1280,720 };		// ���ڴ�С
	//const float damping = 0.1f;			// ����ϵ��������ƽ���ȺͲ���Ч��
	//Vector2 velocity;						// ��������ƶ��ٶȣ���̬�����Ա���״̬

	SDL_Renderer* renderer;					// 
	Vector2 pos;							// �����λ��
	Vector2 last_pos;						// ��һ�������λ��
	float shaking_strength = 0;				// �������ȴ�С

};

