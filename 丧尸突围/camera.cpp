#include "camera.h"

Camera::Camera(SDL_Renderer* renderer) {
	this->renderer = renderer;
}

Camera::~Camera() = default;

void Camera::on_update(float delta) {

}

void Camera::follow_pos(Vector2 target_pos) {
	Vector2 offset = pos;
	offset.x = target_pos.x - window_size.x / 2;
    offset.y = target_pos.y - window_size.y * 2 / 3;
	set_pos(offset);
}

void Camera::follow_pos(Vector2 follow_pos, bool is_facing_right) {
	Vector2 offset;
	offset.x = follow_pos.x - window_size.x / 2 + (is_facing_right ? window_size.x / 8 : -window_size.x / 8);
	offset.y = follow_pos.y - window_size.y * 2 / 3;

	Vector2 distance = offset - pos;

	if (distance.length() > move_speed) {
		Vector2 velocity = distance * move_speed;
		pos += velocity;
	}
	else {
		pos = offset;
	}
}

void Camera::fill_rect(const SDL_Rect* rect, SDL_Color color) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	SDL_Rect rect_dst = *rect;
	rect_dst.x -= pos.x;
	rect_dst.y -= pos.y;

	SDL_RenderFillRect(renderer, &rect_dst);
	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
}

void Camera::draw_rect(const SDL_Rect* rect, SDL_Color color) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	SDL_Rect rect_dst = *rect;
	rect_dst.x -= pos.x;
	rect_dst.y -= pos.y;

	SDL_RenderDrawRect(renderer, &rect_dst);
	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
}

void Camera::draw_rect(const SDL_FRect* rect, SDL_Color color) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	SDL_Rect rect_dst;
	rect_dst.x = rect->x - pos.x;
	rect_dst.y = rect->y - pos.y;
	rect_dst.w = rect->w;
	rect_dst.h = rect->h;

	SDL_RenderDrawRect(renderer, &rect_dst);
	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
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
		SDL_FreeSurface(surface);
	}

	SDL_FRect rect_dst;
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

void Camera::render_texture(SDL_Texture* texture, const SDL_Rect* rect_src, const SDL_FRect* rect_dst, 
	double angle, const SDL_FPoint* center, SDL_RendererFlip flip) const {
	SDL_FRect rect_dst_win = *rect_dst;
	rect_dst_win.x -= pos.x;
	rect_dst_win.y -= pos.y;

	SDL_RenderCopyExF(renderer, texture, rect_src, &rect_dst_win, angle, center, flip);
}
