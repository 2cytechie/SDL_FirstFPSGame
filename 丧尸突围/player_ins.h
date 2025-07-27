#pragma once

#include "player.h"

class Knight :public Player {
public:
	Knight() {
		name = "Knight";
		animation_magnification = 3.0f;
		animation_frame_delta = 0.15f;

		hit_box->set_size({ 140,100 });
		hurt_box->set_size({ 50,100 });
		block_box->set_size({ 50,100 });
	}

	~Knight() = default;

};

class Soldier :public Player {
public:
	Soldier() {
		name = "Soldier";
		animation_magnification = 2.5f;
		animation_frame_delta = 0.15f;

		hit_box->set_size({ 150,110 });
		hurt_box->set_size({ 60,100 });
		block_box->set_size({ 60,100 });
	}

	~Soldier() = default;

};

class Sprites :public Player {
public:
	Sprites() {
		name = "Sprites";

		animation_magnification = 3.0f;
		animation_frame_delta = 0.15f;

		hit_box->set_size({ 140,100 });
		hurt_box->set_size({ 50,100 });
		block_box->set_size({ 50,100 });
	}

	~Sprites() = default;

};

class Pexel :public Player {
public:
	Pexel() {
		name = "Pexel";

		animation_magnification = 3.0f;
		animation_frame_delta = 0.15f;

		hit_box->set_size({ 100,140 });
		hurt_box->set_size({ 50,80 });
		block_box->set_size({ 50,80 });
	}

	~Pexel() = default;

};

class Fighter :public Player {
public:
	Fighter() {
		name = "Fighter";

		animation_magnification = 1.2f;
		animation_frame_delta = 0.15f;

		hit_box->set_size({ 100,100 });
		hurt_box->set_size({ 50,100 });
		block_box->set_size({ 50,100 });
	}

	~Fighter() = default;

};

class Samurai :public Player {
public:
	Samurai() {
		name = "Samurai";

		animation_magnification = 1.2f;
		animation_frame_delta = 0.15f;

		hit_box->set_size({ 100,100 });
		hurt_box->set_size({ 50,100 });
		block_box->set_size({ 50,100 });
	}

	~Samurai() = default;

};

class Martial :public Player {
public:
	Martial() {
		name = "Martial";

		animation_magnification = 2.0f;
		animation_frame_delta = 0.2f;

		hit_box->set_size({ 160,120 });
		hurt_box->set_size({ 45,110 });
		block_box->set_size({ 45,110 });
	}

	~Martial() = default;

};
