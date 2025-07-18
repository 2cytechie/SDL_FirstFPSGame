#pragma once

#include "character.h"

class Item : public Character {


	void on_input(const SDL_Event& msg) override;
	void on_update(float delta) override;
	void on_render(Camera& camera)override;

	void on_hurt() override;

	void attack();
	void jump();
	void dash();



};
