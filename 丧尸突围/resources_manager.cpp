#include "util.h"
#include "resources_manager.h"

ResourcesManager* ResourcesManager::manager = nullptr;

ResourcesManager* ResourcesManager::instance() {
	if (!manager) {
		manager = new ResourcesManager();
	}
	return manager;
}

ResourcesManager::ResourcesManager() = default;

ResourcesManager::~ResourcesManager() = default;

struct ImageResInfo {
	std::string id;
	LPCTSTR path;
};

struct AtlasResInfo {
	std::string id;
	LPCTSTR path;
	int num_frame = 0;
};

static const std::vector<ImageResInfo> image_info_list = {

};

static const std::vector<AtlasResInfo> atlas_info_list = {

};

// 检查资源是否加载成功
static inline bool check_image_valid(IMAGE* image) {
	return GetImageBuffer(image);
}

// 加载资源
void ResourcesManager::load() {
	for (const auto& info : image_info_list) {
		IMAGE* image = new IMAGE();
		loadimage(image, info.path);
		if (!check_image_valid(image)) {
			throw info.path;		// 抛出异常
		}
		image_pool[info.id] = image;
	}

	for (const auto& info : atlas_info_list) {
		Atlas* atlas = new Atlas();
		atlas->load(info.path, info.num_frame);
		for (int i = 0; i < atlas->get_size(); i++) {
			IMAGE* image = atlas->get_image(i);
			if (!check_image_valid(image)) {
				throw info.path;	// 抛出错误
			}
		}
		atlas_pool[info.id] = atlas;
	}

	// 加载资源

}

Atlas* ResourcesManager::find_atlas(const std::string& id) const {
	const auto& itor = atlas_pool.find(id);
	if (itor == atlas_pool.end()) {
		return nullptr;
	}
	return itor->second;

}

IMAGE* ResourcesManager::find_image(const std::string& id) const {
	const auto& itor = image_pool.find(id);
	if (itor == image_pool.end()) {
		return nullptr;
	}
	return itor->second;
}

// 图片反转
void ResourcesManager::flip_image(IMAGE* src_image, IMAGE* dst_image, int num_h) {
	int w = src_image->getwidth();
	int h = src_image->getheight();
	int w_frame = w / num_h;

	Resize(dst_image, w, h);
	DWORD* src_buffer = GetImageBuffer(src_image);
	DWORD* dst_buffer = GetImageBuffer(dst_image);
	for (int i = 0; i < num_h; i++) {
		int x_left = i * w_frame;
		int x_right = (i + 1) * w_frame;
		for (int y = 0; y < h; y++) {
			for (int x = x_left; x < x_right; x++) {
				int idx_src = y * w + x;
				int idx_dst = y * w + x_right - (x - x_left);
				dst_buffer[idx_dst] = src_buffer[idx_src];
			}
		}
	}
}

void ResourcesManager::flip_image(const std::string& src_id, const std::string dst_id, int num_h) {
	IMAGE* src_image = image_pool[src_id];
	IMAGE* dst_image = new IMAGE();

	flip_image(src_image, dst_image, num_h);

	image_pool[dst_id] = dst_image;
}

void ResourcesManager::flip_atlas(const std::string& src_id, const std::string dst_id) {
	Atlas* src_atlas = atlas_pool[src_id];
	Atlas* dst_atlas = new Atlas();
	for (int i = 0; i < src_atlas->get_size(); i++) {
		IMAGE img_flipped;
		flip_image(src_atlas->get_image(i), &img_flipped);
		dst_atlas->add_image(img_flipped);
	}

	atlas_pool[dst_id] = dst_atlas;
}

