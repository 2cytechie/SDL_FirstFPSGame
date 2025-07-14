#include "camera.h"

Camera::Camera(SDL_Renderer* renderer) {
	this->renderer = renderer;

	timer_shake.set_one_shot(true);
	timer_shake.set_on_timeout([&] {
		is_shaking = false;
		reset();
		});
}

Camera::~Camera() = default;

void Camera::on_update(float delta) {
	timer_shake.on_update(delta);

	if (is_shaking) {
		pos.x = (-50 + rand() % 100) / 50.0f * shaking_strength;
		pos.y = (-50 + rand() % 100) / 50.0f * shaking_strength;
	}
}

void Camera::shake(float strength, float duration) {
	is_shaking = true;
	shaking_strength = strength;

	timer_shake.set_wait_time(duration);
	timer_shake.restart();
}

void Camera::set_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void Camera::fill_rect(const SDL_Rect* rect) {
	SDL_Rect rect_dst = *rect;
	rect_dst.x -= pos.x;
	rect_dst.y -= pos.y;

	SDL_RenderFillRect(renderer, &rect_dst);
}

void Camera::draw_rect(const SDL_Rect* rect) {
	SDL_Rect rect_dst = *rect;
	rect_dst.x -= pos.x;
	rect_dst.y -= pos.y;

	SDL_RenderDrawRect(renderer, &rect_dst);
}

void Camera::draw_text(Text* text) {
	if (!text->texture) {
		if (!text->font || text->text.empty()) return;

		SDL_Surface* surface = nullptr;
		// 创建新surface
		if (text->background_color.a == 0) {
			surface = TTF_RenderUTF8_Blended(text->font, text->text.c_str(), text->color);
		}
		else {
			surface = TTF_RenderUTF8_Shaded(text->font, text->text.c_str(), text->color, text->background_color);
		}

		if (!surface) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "表面创建失败: %s", TTF_GetError());
			return;
		}

		text->size.x = surface->w, text->size.y = surface->h;
		text->texture = SDL_CreateTextureFromSurface(renderer, surface);
	}

	SDL_Rect rect_dst;
	switch (text->type) {
	case Text::TextType::Center:
		rect_dst.x = text->position.x - text->size.x / 2;
		rect_dst.y = text->position.y - text->size.y / 2;
		break;
	case Text::TextType::Left:
		rect_dst.x = text->position.x;
		rect_dst.y = text->position.y - text->size.y / 2;
		break;
	case Text::TextType::Right:
		rect_dst.x = text->position.x - text->size.x;
		rect_dst.y = text->position.y - text->size.y;
		break;
	}
	rect_dst.w = text->size.x;
	rect_dst.h = text->size.y;

	render_texture(text->texture, nullptr, &rect_dst, 0, nullptr);
}

void Camera::render_texture(SDL_Texture* texture, const SDL_Rect* rect_src, const SDL_Rect* rect_dst, 
	double angle, const SDL_Point* center, SDL_RendererFlip flip) const {
	SDL_Rect rect_dst_win = *rect_dst;
	rect_dst_win.x -= pos.x;
	rect_dst_win.x -= pos.x;

	SDL_RenderCopyEx(renderer, texture, rect_src, &rect_dst_win, angle, center, flip);
}
