#pragma once
#include "player.h"

class Soldier :public Player {
public:
	Soldier() {
		name = "Soldier";
		animation_magnification = 2.5f;
		animation_frame_delta = 0.1f;

		hit_box->set_size({ 150,110 });
		hurt_box->set_size({ 60,100 });
		
		Player::init();
	}

	~Soldier() = default;

};

class Sprites :public Player {
public:
	Sprites() {
		name = "Sprites";
		animation_magnification = 3.0f;
		animation_frame_delta = 0.1f;

		hit_box->set_size({ 140,100 });
		hurt_box->set_size({ 50,100 });
		
		Player::init();
	}

	~Sprites() = default;

};

class Pexel :public Player {
public:
	Pexel() {
		name = "Pexel";
		animation_magnification = 3.0f;
		animation_frame_delta = 0.08f;

		hit_box->set_size({ 100,140 });
		hurt_box->set_size({ 50,85 });
		
		Player::init();
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
		
		Player::init();
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
		
		Player::init();
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
		
		Player::init();
	}

	~Martial() = default;

};
