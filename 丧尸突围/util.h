#pragma once

// 生成随机数
inline int range_random(int min_num, int max_num) {
	return min_num + rand() % (max_num - min_num + 1);
}