#pragma once

#include "res_mgr.h"
#include "character.h"

class Player : public Character {
public:
	enum class PlayerState {
		Idle,
		Run,
		Attack,
		Jump,
		Death
	};

	Player() {

	}
	

private:
	PlayerState state;
	Animation* current_animation = nullptr;

};
