#include "player_state_node.h"
#include "level_mgr.h"
#include "scene_mgr.h"
#include "util.h"

void PlayerAttackState::on_enter(Player* player) {
	player->set_animation("Attack");

	timer.set_wait_time(player->get_current_animation_time());
	timer.set_one_shot(true);
	timer.set_on_timeout([player]()
		{
			player->set_attacking(false);
		});

	player->get_hit_box()->set_enabled(true);
	player->set_attacking(true);
	update_hit_box_pos(player);
	player->attack();
	timer.restart();

	switch (range_random(1, 3))
	{
	case 1:
		Mix_PlayChannel(-1, ResMgr::instance()->find_audio("player_attack_1"), 0);
		break;
	case 2:
		Mix_PlayChannel(-1, ResMgr::instance()->find_audio("player_attack_2"), 0);
		break;
	case 3:
		Mix_PlayChannel(-1, ResMgr::instance()->find_audio("player_attack_3"), 0);
		break;
	}
}

void PlayerAttackState::on_update(Player* player, float delta) {
	timer.on_update(delta);
	update_hit_box_pos(player);

	if (player->get_hp() <= 0)
		player->switch_state("Death");
	else if (!player->get_attacking())
	{
		if (player->get_move_axis() == 0)
			player->switch_state("Idle");
		else if (player->is_on_floor() && player->get_move_axis() != 0)
			player->switch_state("Run");
	}
}

void PlayerAttackState::on_exit(Player* player) {
	player->get_hit_box()->set_enabled(false);
}

void PlayerAttackState::update_hit_box_pos(Player* player) {
	CollisionBox* hit_box = player->get_hit_box();
	Vector2 size_hit_box = hit_box->get_size();
	Vector2 player_pos = player->get_pos();
	Vector2 pos_hit_box = player_pos;
	pos_hit_box.y -= size_hit_box.y / 2;
	pos_hit_box.x += (player->facing_right() ? size_hit_box.x : -size_hit_box.x) / 2;
	hit_box->set_pos(pos_hit_box);
}

PlayerDeathState::PlayerDeathState()
{
	timer.set_wait_time(0.5f);
	timer.set_one_shot(true);
	timer.set_on_timeout([&]()
		{
			SceneMgr::instance()->switch_to(SceneMgr::SceneType::GameOver);
		});
}

void PlayerDeathState::on_enter(Player* player)
{
	player->set_animation("Death");
}

void PlayerDeathState::on_update(Player* player, float delta)
{
	timer.on_update(delta);
}

void PlayerIdleState::on_enter(Player* player)
{
	player->set_animation("Idle");
}

void PlayerIdleState::on_update(Player* player, float delta)
{
	if (SceneMgr::instance()->get_scene_type() != SceneMgr::SceneType::Edit) {
		if (player->get_hp() <= 0)
			player->switch_state("Death");
		else if (player->can_attack())
			player->switch_state("Attack");
		else if (player->can_jump())
			player->switch_state("Jump");
		else if (player->can_dash())
			player->switch_state("Dash");
		else if (player->is_on_floor() && player->get_move_axis() != 0)
			player->switch_state("Run");
	}
}

void PlayerJumpState::on_enter(Player* player)
{
	player->set_animation("Jump");
	player->jump();

	Mix_PlayChannel(-1, ResMgr::instance()->find_audio("player_jump"), 0);
}

void PlayerJumpState::on_update(Player* player, float delta)
{
	if (player->get_hp() <= 0)
		player->switch_state("Death");
	else if (player->can_attack())
		player->switch_state("Attack");
	else if(player->is_on_floor())
		player->switch_state("Idle");
	else if (player->can_dash())
		player->switch_state("Dash");
	else if (player->can_jump())
		player->switch_state("Jump");
}

PlayerDashState::PlayerDashState() {
	timer.set_wait_time(0.1f);
	timer.set_one_shot(true);
	timer.set_on_timeout([&]()
		{
			Player* player = LevelMgr::instance()->get_player();
			player->set_dashing(false);
		});
}

void PlayerDashState::on_enter(Player* player)
{
	player->set_animation("Idle");

	player->get_hurt_box()->set_enabled(false);
	player->set_dashing(true);
	player->dash();
	timer.restart();

	Mix_PlayChannel(-1, ResMgr::instance()->find_audio("player_dash"), 0);
}

void PlayerDashState::on_update(Player* player, float delta)
{
	timer.on_update(delta);

	if (!player->get_dashing())
	{
		if (player->get_move_axis() != 0)
			player->switch_state("Run");
		else if (player->can_jump())
			player->switch_state("Jump");
		else
			player->switch_state("Idle");
	}
}

void PlayerDashState::on_exit(Player* player)
{
	player->get_hurt_box()->set_enabled(true);
}

void PlayerRunState::on_enter(Player* player)
{
	player->set_animation("Run");

	Mix_PlayChannel(1, ResMgr::instance()->find_audio("player_run"), -1);
}

void PlayerRunState::on_update(Player* player, float delta)
{
	if (player->get_hp() <= 0)
		player->switch_state("Death");
	else if (player->can_attack())
		player->switch_state("Attack");
	else if (player->get_move_axis() == 0)
		player->switch_state("Idle");
	else if (player->can_jump())
		player->switch_state("Jump");
	else if (player->can_dash())
		player->switch_state("Dash");
}

void PlayerRunState::on_exit(Player* player) {
	Mix_HaltChannel(1);
}
