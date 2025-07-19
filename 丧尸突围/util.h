#pragma once

// 生成随机数
inline int range_random(int min_num, int max_num) {
	return min_num + rand() % (max_num - min_num + 1);
}

inline float range_randomF(float min_num, float max_num) {
    float random_fraction = (float)rand() / (float)RAND_MAX;
    return min_num + random_fraction * (max_num - min_num);
}