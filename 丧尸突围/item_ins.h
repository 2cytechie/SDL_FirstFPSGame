#pragma once
#include "item.h"

class grass_plant :public Item {
public:
	grass_plant(Vector2 p) : Item(p) {
		name = "grass_plant";
		animation_magnification = 1.3f;
		animation_frame_delta = 999.0f;
		is_block = true;

		Item::init();
	}

	~grass_plant() = default;
};

class plant :public Item {
public:
	plant(Vector2 p) : Item(p) {
		name = "plant";
		animation_magnification = 1.3f;
		animation_frame_delta = 999.0f;
		is_block = true;

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

		Item::init();
	}
	
	~notebook() = default;
};

class bridge_left :public Item {
public:
	bridge_left(Vector2 p) : Item(p) {
		name = "bridge_left";
		animation_magnification = 2.0f;
		animation_frame_delta = 999.0f;

		Item::init();
	}

	~bridge_left() = default;
};

class bridge_mid :public Item {
public:
	bridge_mid(Vector2 p) : Item(p) {
		name = "bridge_mid";
		animation_magnification = 2.0f;
		animation_frame_delta = 999.0f;

		Item::init();
	}

	~bridge_mid() = default;
};

class bridge_right :public Item {
public:
	bridge_right(Vector2 p) : Item(p) {
		name = "bridge_right";
		animation_magnification = 2.0f;
		animation_frame_delta = 999.0f;

		Item::init();
	}

	~bridge_right() = default;
};

class stream :public Item {
public:
	stream(Vector2 p) : Item(p) {
		name = "stream";
		animation_magnification = 2.8f;
		animation_frame_delta = 0.2f;

		Item::init();
	}

	~stream() = default;
};

class waterfall :public Item {
public:
	waterfall(Vector2 p) : Item(p) {
		name = "waterfall";
		animation_magnification = 7.6f;
		animation_frame_delta = 0.2f;

		Item::init();
	}

	~waterfall() = default;
};

class BoxCat :public Item {
public:
	BoxCat(Vector2 p) : Item(p) {
		name = "BoxCat";
		animation_magnification = 1.5f;
		animation_frame_delta = 0.2f;

		Item::init();
	}

	~BoxCat() = default;
};

class bush :public Item {
public:
	bush(Vector2 p) : Item(p) {
		name = "bush2";
		animation_magnification = 1.0f;
		animation_frame_delta = 999.0f;

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