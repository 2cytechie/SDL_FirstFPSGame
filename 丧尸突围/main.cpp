#include<chrono>
#include<thread>
#include<graphics.h>

int main(int argc, char** argv) {
	using namespace std::chrono;

	HWND hwnd = initgraph(1280, 720);


	const nanoseconds frame_duration(1000000000 / 144);
	steady_clock::time_point last_tick = steady_clock::now();

	ExMessage msg;
	bool is_quit = false;

	BeginBatchDraw();

	while (!is_quit) {
		while (peekmessage(&msg)) {
			// 键鼠输入
		}

		steady_clock::time_point frame_start = steady_clock::now();
		duration<float> delta = duration<float>(frame_start - last_tick);

		// 数据处理


		// 画面渲染

		FlushBatchDraw();

		last_tick = frame_start;
		nanoseconds sleep_duration = frame_duration - (steady_clock::now() - frame_start);
		if (sleep_duration > nanoseconds(0)) {
			std::this_thread::sleep_for(sleep_duration);
		}

	}

	EndBatchDraw();

	return 0;
}