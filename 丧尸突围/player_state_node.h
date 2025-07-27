#pragma once

#include "player.h"
#include "state_node.h"
#include "timer.h"

class PlayerAttackState : public StateNode<Player>
{
public:
	PlayerAttackState() = default;
	~PlayerAttackState() = default;

	void on_enter(Player* player) override;
	void on_update(Player* player, float delta) override;
	void on_exit(Player* player) override;

private:
	Timer timer;

	void update_hit_box_pos(Player* player);

};

class PlayerDeathState : public StateNode<Player>
{
public:
	PlayerDeathState();
	~PlayerDeathState() = default;

	void on_enter(Player* player) override;
	void on_update(Player* player, float delta) override;

private:
	Timer timer;

};

class PlayerIdleState : public StateNode<Player>
{
public:
	PlayerIdleState() = default;
	~PlayerIdleState() = default;

	void on_enter(Player* player) override;
	void on_update(Player* player, float delta) override;

private:

};

class PlayerJumpState : public StateNode<Player>
{
public:
	PlayerJumpState() = default;
	~PlayerJumpState() = default;

	void on_enter(Player* player) override;
	void on_update(Player* player, float delta) override;

private:

};

class PlayerRunState : public StateNode<Player>
{
public:
	PlayerRunState() = default;
	~PlayerRunState() = default;

	void on_enter(Player* player) override;
	void on_update(Player* player, float delta) override;
	void on_exit(Player* player) override;

private:

};

class PlayerDashState : public StateNode<Player>
{
public:
	PlayerDashState();
	~PlayerDashState() = default;

	void on_enter(Player* player) override;
	void on_update(Player* player, float delta) override;
	void on_exit(Player* player) override;

private:
	Timer timer;

};
