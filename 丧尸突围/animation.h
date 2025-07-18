#pragma once

#include "timer.h"
#include "camera.h"

#include<vector>
#include<functional>
#include<SDL_image.h>

extern bool DEBUG;

class Animation {
public:
	enum class AnchorMode {
		Centered,					// 居中锚点
		BottomCentered				// 底部锚点
	};

public:
	Animation() {
		timer.set_one_shot(false);
		timer.set_on_timeout([&]() {
			idx_frame++;
			if (idx_frame >= frame_count) {
				idx_frame = is_loop ? 0 : frame_count - 1;
				if (!is_loop && on_finished) {
					on_finished();
				}
			}
			});
	}

	~Animation() = default;

	void load(SDL_Texture* texture, int animation_frame) {
		if (this->texture) {
			SDL_DestroyTexture(this->texture);
		}

		this->texture = texture;
		frame_count = animation_frame;
		timer.set_wait_time(0.15f);
		int width, height;
		SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
		frame_size.x = width / animation_frame;
		frame_size.y = height;
		size = frame_size;
	}
	void load(std::vector<SDL_Texture*> tex_list,float delta) {
		animation_list.clear();
		animation_list = tex_list;
		frame_count = tex_list.size();
		timer.set_wait_time(delta);
		int width, height;
		SDL_QueryTexture(tex_list[0], nullptr, nullptr, &width, &height);
		frame_size.x = width;
		frame_size.y = height;
		size = frame_size;
	}

	void on_update(float delta) {
		timer.on_update(delta);
	}

	void on_render(Camera& camera, bool facing_right = true) {
		// 是否翻转图片
		SDL_RendererFlip flip = facing_right ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;

		if (texture) {
			SDL_Rect rect_src;
			SDL_FRect rect_dst;
			rect_src.x = idx_frame * frame_size.x;
			rect_src.y = 0;
			rect_src.w = frame_size.x;
			rect_src.h = frame_size.y;

			rect_dst.x = (int)pos.x - size.x / 2;
			rect_dst.y = (anchor_mode == AnchorMode::Centered) ? (int)pos.y - size.y / 2 : (int)pos.y - size.y;
			rect_dst.w = size.x;
			rect_dst.h = size.y;

			if (DEBUG) {
				SDL_Color color{ 0, 255, 0, 255 };
				camera.draw_rect(&rect_dst, color);
			}

			camera.render_texture(texture, &rect_src, &rect_dst, 0, nullptr, flip);
			return;
		}

		if (animation_list.size() > 0) {
			SDL_FRect rect_dst;
			rect_dst.x = (int)pos.x - frame_size.x / 2;
			rect_dst.y = (anchor_mode == AnchorMode::Centered) ? (int)pos.y - frame_size.y / 2 : (int)pos.y - frame_size.y;
			rect_dst.w = size.x;
			rect_dst.h = size.y;

			if (DEBUG) {
				SDL_Color color{ 0, 255, 0, 255 };
				camera.draw_rect(&rect_dst, color);
			}

			camera.render_texture(animation_list[idx_frame], nullptr, &rect_dst, 0, nullptr, flip);
			return;
		}
	}

	void reset() {
		timer.restart();
		idx_frame = 0;
		//size = frame_size;
	}

	// 锚点模式
	void set_anchor_mode(AnchorMode mode) {
		anchor_mode = mode;
	}

	void set_pos(int x,int y) {
		pos.x = x;
		pos.y = y;
	}

	void set_pos(const Vector2& pos) {
		this->pos = pos;
	}

	void set_size(const Vector2& size) {
		this->size = size;
	}

	// 等比例缩放
	void set_size(const float scale) {
		this->size = frame_size * scale;
	}

	// 是否循环播放
	void set_loop(bool flag) {
		is_loop = flag;
	}

	void set_interval(float interval) {
		timer.set_wait_time(interval);
	}

	void set_on_finished(std::function<void()> on_finished) {
		this->on_finished = on_finished;
	}

private:
	Timer timer;
	Vector2 pos;
	Vector2 size;
	Vector2 frame_size;
	bool is_loop = true;
	size_t frame_count = 0;
	size_t idx_frame = 0;
	SDL_Texture* texture = nullptr;
	std::vector<SDL_Texture*> animation_list;					// GIF格式
	std::function<void()> on_finished;
	AnchorMode anchor_mode = AnchorMode::BottomCentered;

};
