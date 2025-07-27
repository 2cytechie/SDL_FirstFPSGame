#pragma once

#include "enemy.h"

class FlyingEye : public Enemy {
public:
    FlyingEye(Vector2 revive_pos) : Enemy(revive_pos) {
        name = "FlyingEye";
        hp = 100;
        max_hp = 100;

        animation_magnification = 3.0f;
        animation_frame_delta = 0.15f;

        hit_box->set_size({ 100,120 });
        hurt_box->set_size({ 60,100 });
    }

    ~FlyingEye() = default;
};

class Goblin : public Enemy {
public:
    Goblin(Vector2 revive_pos) : Enemy(revive_pos) {
        name = "Goblin";
        hp = 100;
        max_hp = 100;

        animation_magnification = 3.0f;
        animation_frame_delta = 0.15f;

        hit_box->set_size({ 100,120 });
        hurt_box->set_size({ 60,100 });
    }

    ~Goblin() = default;
};

class Mushroom : public Enemy {
public:
    Mushroom(Vector2 revive_pos) : Enemy(revive_pos) {
        name = "Mushroom";
        hp = 100;
        max_hp = 100;

        animation_magnification = 3.0f;
        animation_frame_delta = 0.15f;

        hit_box->set_size({ 100,120 });
        hurt_box->set_size({ 60,100 });
    }

    ~Mushroom() = default;
};

class Skeleton : public Enemy {
public:
    Skeleton(Vector2 revive_pos) : Enemy(revive_pos) {
        name = "Skeleton";
        hp = 100;
        max_hp = 100;

        animation_magnification = 3.0f;
        animation_frame_delta = 0.15f;

        hit_box->set_size({ 100,120 });
        hurt_box->set_size({ 60,100 });
    }

    ~Skeleton() = default;
};

class SpriteSheets : public Enemy {
public:
    SpriteSheets(Vector2 revive_pos) : Enemy(revive_pos) {
        name = "SpriteSheets";
        hp = 100;
        max_hp = 100;

        animation_magnification = 3.0f;
        animation_frame_delta = 0.15f;

        hit_box->set_size({ 100,120 });
        hurt_box->set_size({ 60,100 });
    }

    ~SpriteSheets() = default;
};

class Ninja : public Enemy {
public:
    Ninja(Vector2 revive_pos) : Enemy(revive_pos) {
        name = "Ninja";
        hp = 100;
        max_hp = 100;

        animation_magnification = 3.0f;
        animation_frame_delta = 0.15f;

        hit_box->set_size({ 100,120 });
        hurt_box->set_size({ 60,100 });
    }

    ~Ninja() = default;
};

class Minotaur : public Enemy {
public:
    Minotaur(Vector2 revive_pos) : Enemy(revive_pos) {
        name = "Minotaur";
        hp = 100;
        max_hp = 100;

        animation_magnification = 3.0f;
        animation_frame_delta = 0.15f;

        hit_box->set_size({ 100,120 });
        hurt_box->set_size({ 60,100 });
    }

    ~Minotaur() = default;
};

class Slime1 : public Enemy {
public:
    Slime1(Vector2 revive_pos) : Enemy(revive_pos) {
        name = "Slime1";
        hp = 100;
        max_hp = 100;

        animation_magnification = 3.0f;
        animation_frame_delta = 0.15f;

        hit_box->set_size({ 100,120 });
        hurt_box->set_size({ 60,100 });
    }

    ~Slime1() = default;
};

class Slime2 : public Enemy {
public:
    Slime2(Vector2 revive_pos) : Enemy(revive_pos) {
        name = "Slime2";
        hp = 100;
        max_hp = 100;

        animation_magnification = 3.0f;
        animation_frame_delta = 0.15f;

        hit_box->set_size({ 100,120 });
        hurt_box->set_size({ 60,100 });
    }

    ~Slime2() = default;
};