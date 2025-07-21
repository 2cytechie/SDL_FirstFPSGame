#pragma once

#include "player.h"

class Knight :public Player {
public:
	Knight() {
		name = "Knight";
		hp = 100;
		max_hp = 100;
		pos = Vector2(100, 100);
		logic_height = 120;

		animation_magnification = 3.0f;
		animation_frame_delta = 0.15f;

		hit_box->set_size({ 100,120 });
		hurt_box->set_size({ 60,100 });
	}

	~Knight() = default;

};

class Soldier :public Player {
public:
	Soldier() {
		name = "Soldier";
		hp = 100;
		max_hp = 100;
		pos = Vector2(100, 100);
		logic_height = 120;

		animation_magnification = 3.0f;
		animation_frame_delta = 0.15f;

		hit_box->set_size({ 100,120 });
		hurt_box->set_size({ 60,100 });
	}

	~Soldier() = default;

};

class Sprites :public Player {
public:
	Sprites() {
		name = "Sprites";
		hp = 100;
		max_hp = 100;
		pos = Vector2(100, 100);
		logic_height = 120;

		animation_magnification = 3.0f;
		animation_frame_delta = 0.15f;

		hit_box->set_size({ 100,120 });
		hurt_box->set_size({ 60,100 });
	}

	~Sprites() = default;

};

class Pexel :public Player {
public:
	Pexel() {
		name = "Pexel";
		hp = 100;
		max_hp = 100;
		pos = Vector2(100, 100);
		logic_height = 120;

		animation_magnification = 3.0f;
		animation_frame_delta = 0.15f;

		hit_box->set_size({ 100,120 });
		hurt_box->set_size({ 60,100 });
	}

	~Pexel() = default;

};

class Fighter :public Player {
public:
	Fighter() {
		name = "Fighter";
		hp = 100;
		max_hp = 100;
		pos = Vector2(100, 100);
		logic_height = 120;

		animation_magnification = 3.0f;
		animation_frame_delta = 0.15f;

		hit_box->set_size({ 100,120 });
		hurt_box->set_size({ 60,100 });
	}

	~Fighter() = default;

};

class Samurai :public Player {
public:
	Samurai() {
		name = "Samurai";
		hp = 100;
		max_hp = 100;
		pos = Vector2(100, 100);
		logic_height = 120;

		animation_magnification = 3.0f;
		animation_frame_delta = 0.15f;

		hit_box->set_size({ 100,120 });
		hurt_box->set_size({ 60,100 });
	}

	~Samurai() = default;

};

class Martial :public Player {
public:
	Martial() {
		name = "Martial";
		hp = 100;
		max_hp = 100;
		pos = Vector2(100, 100);
		logic_height = 120;

		animation_magnification = 3.0f;
		animation_frame_delta = 0.15f;

		hit_box->set_size({ 100,120 });
		hurt_box->set_size({ 60,100 });
	}

	~Martial() = default;

};
