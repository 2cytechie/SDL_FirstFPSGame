#pragma once
#include "item.h"

class plant :public Item {
public:
	plant(Vector2 p) : Item(p) {
		name = "plant";
		animation_magnification = 0.5f;
		animation_frame_delta = 999.0f;
		block_box->set_size({ 9999,100 });

		Item::init();
	}

	~plant() = default;
};

class notebook :public Item {
public:
	notebook(Vector2 p) : Item(p) {
		name = "notebook";
		animation_magnification = 0.2f;
		animation_frame_delta = 999.0f;
		block_box->set_size({ 76,50 });

		Item::init();
	}
	
	~notebook() = default;
};

class BoxCat :public Item {
public:
	BoxCat(Vector2 p) : Item(p) {
		name = "BoxCat";
		animation_magnification = 1.5f;
		animation_frame_delta = 0.2f;
		block_box->set_size({ 48,48 });

		Item::init();
	}

	~BoxCat() = default;
};

class bush :public Item {
public:
	bush(Vector2 p) : Item(p) {
		name = "bush";
		animation_magnification = 1.0f;
		animation_frame_delta = 999.0f;
		block_box->set_size({ 30,30 });

		Item::init();
	}

	~bush() = default;
};

class rock_1 :public Item {
public:
	rock_1(Vector2 p) : Item(p) {
		name = "rock_1";
		animation_magnification = 2.0f;
		animation_frame_delta = 999.0f;
		block_box->set_size({ 40,24 });

		Item::init();
	}

	~rock_1() = default;
};

class rock_2 :public Item {
public:
	rock_2(Vector2 p) : Item(p) {
		name = "rock_2";
		animation_magnification = 2.0f;
		animation_frame_delta = 999.0f;
		block_box->set_size({ 53,26 });

		Item::init();
	}

	~rock_2() = default;
};

class rock_3 :public Item {
public:
	rock_3(Vector2 p) : Item(p) {
		name = "rock_3";
		animation_magnification = 2.0f;
		animation_frame_delta = 999.0f;
		block_box->set_size({ 90,38 });

		Item::init();
	}

	~rock_3() = default;
};

class sleepBlackCat :public Item {
public:
	sleepBlackCat(Vector2 p) : Item(p) {
		name = "sleepBlackCat";
		animation_magnification = 1.0f;
		animation_frame_delta = 0.15f;
		block_box->set_size({ 60,50 });

		Item::init();
	}

	~sleepBlackCat() = default;
};

class stone1 :public Item {
public:
	stone1(Vector2 p) : Item(p) {
		name = "stone1";
		animation_magnification = 2.0f;
		animation_frame_delta = 999.0f;
		block_box->set_size({ 35,30 });

		Item::init();
	}

	~stone1() = default;
};

class stone2 :public Item {
public:
	stone2(Vector2 p) : Item(p) {
		name = "stone2";
		animation_magnification = 2.0f;
		animation_frame_delta = 999.0f;
		block_box->set_size({ 33,28 });

		Item::init();
	}

	~stone2() = default;
};

class streelight :public Item {
public:
	streelight(Vector2 p) : Item(p) {
		name = "streelight";
		animation_magnification = 2.0f;
		animation_frame_delta = 999.0f;
		block_box->set_size({ 30,146 });

		Item::init();
	}

	~streelight() = default;
};

class stump :public Item {
public:
	stump(Vector2 p) : Item(p) {
		name = "stump";
		animation_magnification = 4.0f;
		animation_frame_delta = 999.0f;
		block_box->set_size({ 56,44 });

		Item::init();
	}

	~stump() = default;
};

class tree1 :public Item {
public:
	tree1(Vector2 p) : Item(p) {
		name = "tree1";
		animation_magnification = 3.0f;
		animation_frame_delta = 0.15f;
		block_box->set_size({ 90,200 });

		Item::init();
	}

	~tree1() = default;
};

class trunk :public Item {
public:
	trunk(Vector2 p) : Item(p) {
		name = "trunk";
		animation_magnification = 2.0f;
		animation_frame_delta = 999.0f;
		block_box->set_size({ 62,38 });

		Item::init();
	}

	~trunk() = default;
};

class YellowCat :public Item {
public:
	YellowCat(Vector2 p) : Item(p) {
		name = "YellowCat";
		animation_magnification = 1.5f;
		animation_frame_delta = 0.15f;
		block_box->set_size({ 48,48 });

		Item::init();
	}

	~YellowCat() = default;
};

class background :public Item {
public:
	background(Vector2 p) : Item(p) {
		name = "background";
		relative_camera_speed = 0.3f;
		animation_magnification = 1.0f;
		animation_frame_delta = 999.0f;
		block_box->set_size({ 576,324 });

		block_box->set_enabled(false);

		Item::init();
	}

	~background() = default;
};

class sunsetbackground :public Item {
public:
	sunsetbackground(Vector2 p) : Item(p) {
		name = "sunsetbackground";
		animation_magnification = 1.0f;
		animation_frame_delta = 0.15f;
		block_box->set_size({ 1024,768 });

		block_box->set_enabled(false);

		Item::init();
	}

	~sunsetbackground() = default;
};

class background_layer :public Item {
public:
	background_layer(Vector2 p) : Item(p) {
		name = "background_layer";
		animation_magnification = 4.0f;
		animation_frame_delta = 999.0f;
		block_box->set_size({ 1280,720 });

		block_box->set_enabled(false);

		Item::init();
	}

	~background_layer() = default;
};

class cloud_1 :public Item {
public:
	cloud_1(Vector2 p) : Item(p) {
		name = "cloud_1";
		animation_magnification = 2.0f;
		animation_frame_delta = 999.0f;
		block_box->set_size({ 1152,648 });

		block_box->set_enabled(false);

		Item::init();
	}

	~cloud_1() = default;
};

class cloud_2 :public Item {
public:
	cloud_2(Vector2 p) : Item(p) {
		name = "cloud_2";
		animation_magnification = 2.0f;
		animation_frame_delta = 999.0f;
		block_box->set_size({ 1152,648 });

		block_box->set_enabled(false);

		Item::init();
	}

	~cloud_2() = default;
};

class cloud_3 :public Item {
public:
	cloud_3(Vector2 p) : Item(p) {
		name = "cloud_3";
		animation_magnification = 2.0f;
		animation_frame_delta = 999.0f;
		block_box->set_size({ 1152,648 });

		block_box->set_enabled(false);

		Item::init();
	}

	~cloud_3() = default;
};