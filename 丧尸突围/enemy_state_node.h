#pragma once

#include "Enemy.h"
#include "state_node.h"
#include "timer.h"

class EnemyAttackState : public StateNode<Enemy>
{
public:
    EnemyAttackState() = default;
    ~EnemyAttackState() = default;

    void on_enter(Enemy* enemy) override;
    void on_update(Enemy* enemy, float delta) override;
    void on_exit(Enemy* enemy) override;

private:
    Timer timer;

    void update_hit_box_pos(Enemy* enemy);
};

class EnemyDeathState : public StateNode<Enemy>
{
public:
    EnemyDeathState() = default;
    ~EnemyDeathState() = default;

    void on_enter(Enemy* enemy) override;
    void on_exit(Enemy* enemy) override;

private:

};

class EnemyIdleState : public StateNode<Enemy>
{
public:
    EnemyIdleState() = default;
    ~EnemyIdleState() = default;

    void on_enter(Enemy* enemy) override;
    void on_update(Enemy* enemy, float delta) override;

private:
    Timer timer;

};

class EnemyTakeHitState : public StateNode<Enemy>
{
public:
    EnemyTakeHitState() = default;
    ~EnemyTakeHitState() = default;

    void on_enter(Enemy* enemy) override;
    void on_update(Enemy* enemy, float delta) override;

private:
    Timer timer;

};

class EnemyWalkState : public StateNode<Enemy>
{
public:
    EnemyWalkState() = default;
    ~EnemyWalkState() = default;

    void on_enter(Enemy* enemy) override;
    void on_update(Enemy* enemy, float delta) override;
    void on_exit(Enemy* enemy) override;

private:
    Timer timer;

};

class EnemyPursuitState : public StateNode<Enemy>
{
public:
    EnemyPursuitState() = default;
    ~EnemyPursuitState() = default;

    void on_enter(Enemy* enemy) override;
    void on_update(Enemy* enemy, float delta) override;
    void on_exit(Enemy* enemy) override;

private:

};

class EnemyReturnState : public StateNode<Enemy>
{
public:
    EnemyReturnState() = default;
    ~EnemyReturnState() = default;

    void on_enter(Enemy* enemy) override;
    void on_update(Enemy* enemy, float delta) override;
    void on_exit(Enemy* enemy) override;

private:

};