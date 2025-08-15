#pragma once
#include "enemy.h"

class FlyingEye : public Enemy {
public:
    FlyingEye(Vector2 revive_pos) : Enemy(revive_pos) {
        name = "FlyingEye";
        max_hp = 80;
        Character::attack = 8;

        animation_magnification = 2.0f;
        animation_frame_delta = 0.15f;

        hit_box->set_size({ 100,120 });
        hurt_box->set_size({ 70,60});
        
        Enemy::init();
    }

    ~FlyingEye() = default;
};

class Goblin : public Enemy {
public:
    Goblin(Vector2 revive_pos) : Enemy(revive_pos) {
        name = "Goblin";
        max_hp = 120;
        Character::attack = 10;

        animation_magnification = 2.3f;
        animation_frame_delta = 0.15f;

        hit_box->set_size({ 100,120 });
        hurt_box->set_size({ 70,85 });
        
        Enemy::init();
    }

    ~Goblin() = default;
};

class Mushroom : public Enemy {
public:
    Mushroom(Vector2 revive_pos) : Enemy(revive_pos) {
        name = "Mushroom";
        max_hp = 110;
        Character::attack = 10;

        animation_magnification = 2.6f;
        animation_frame_delta = 0.15f;

        hit_box->set_size({ 100,120 });
        hurt_box->set_size({ 60,100 });
        
        Enemy::init();
    }

    ~Mushroom() = default;
};

class Skeleton : public Enemy {
public:
    Skeleton(Vector2 revive_pos) : Enemy(revive_pos) {
        name = "Skeleton";
        max_hp = 100;
        Character::attack = 8;

        animation_magnification = 2.0f;
        animation_frame_delta = 0.15f;

        hit_box->set_size({ 100,120 });
        hurt_box->set_size({ 60,100 });
        
        Enemy::init();
    }

    ~Skeleton() = default;
};

class SpriteSheets : public Enemy {
public:
    SpriteSheets(Vector2 revive_pos) : Enemy(revive_pos) {
        name = "SpriteSheets";
        max_hp = 100;
        Character::attack = 10;

        animation_magnification = 2.7f;
        animation_frame_delta = 0.15f;

        hit_box->set_size({ 100,120 });
        hurt_box->set_size({ 50,66 });
        
        Enemy::init();
    }

    ~SpriteSheets() = default;
};

class Ninja : public Enemy {
public:
    Ninja(Vector2 revive_pos) : Enemy(revive_pos) {
        name = "Ninja";
        max_hp = 120;
        Character::attack = 15;

        animation_magnification = 2.5f;
        animation_frame_delta = 0.15f;

        hit_box->set_size({ 180,60 });
        hurt_box->set_size({ 60,90 });
        
        Enemy::init();
    }

    ~Ninja() = default;
};

class Minotaur : public Enemy {
public:
    Minotaur(Vector2 revive_pos) : Enemy(revive_pos) {
        name = "Minotaur";
        max_hp = 110;
        Character::attack = 10;

        animation_magnification = 0.78f;
        animation_frame_delta = 0.15f;

        hit_box->set_size({ 100,120 });
        hurt_box->set_size({ 50,75 });
        
        Enemy::init();
    }

    ~Minotaur() = default;
};

class Slime1 : public Enemy {
public:
    Slime1(Vector2 revive_pos) : Enemy(revive_pos) {
        name = "Slime1";
        max_hp = 80;
        Character::attack = 5;

        animation_magnification = 2.0f;
        animation_frame_delta = 0.15f;

        hit_box->set_size({ 100,120 });
        hurt_box->set_size({ 40,40 });
        
        Enemy::init();
    }

    ~Slime1() = default;
};

class Slime2 : public Enemy {
public:
    Slime2(Vector2 revive_pos) : Enemy(revive_pos) {
        name = "Slime2";
        max_hp = 80;
        Character::attack = 5;

        animation_magnification = 2.0f;
        animation_frame_delta = 0.15f;

        hit_box->set_size({ 100,120 });
        hurt_box->set_size({ 40,40 });
        
        Enemy::init();
    }

    ~Slime2() = default;
};