#include "enemy_state_node.h"
#include "level_mgr.h"
#include "scene_mgr.h"
#include "util.h"

void EnemyAttackState::on_enter(Enemy* enemy) {
    std::string res_name = enemy->get_name() + "_" + "Attack";
    enemy->set_animation(res_name);

    timer.set_wait_time(enemy->get_current_animation_time());
    timer.set_one_shot(true);
    timer.set_on_timeout([enemy]()
        {
            enemy->set_attacking(false);
        });

    enemy->get_hit_box()->set_enabled(true);
    enemy->set_attacking(true);
    update_hit_box_pos(enemy);
    enemy->attack();
    timer.restart();

    //switch (range_random(1, 3))
    //{
    //case 1:
    //    Mix_PlayChannel(-1, ResMgr::instance()->find_audio("player_attack_1"), 0);
    //    break;
    //case 2:
    //    Mix_PlayChannel(-1, ResMgr::instance()->find_audio("player_attack_2"), 0);
    //    break;
    //case 3:
    //    Mix_PlayChannel(-1, ResMgr::instance()->find_audio("player_attack_3"), 0);
    //    break;
    //}
}

void EnemyAttackState::on_update(Enemy* enemy, float delta) {
    timer.on_update(delta);
    update_hit_box_pos(enemy);

    if (enemy->get_hp() <= 0)
        enemy->switch_state("Death");
    else if (!enemy->get_attacking())
    {
        Vector2 player_pos = LevelMgr::instance()->get_player()->get_pos();
        if (enemy->can_pursuit(player_pos)) {
            enemy->switch_state("Pursuit");
        }
        else {
            enemy->switch_state("Return");
        }
    }
}

void EnemyAttackState::on_exit(Enemy* enemy) {
    enemy->get_hit_box()->set_enabled(false);
}

void EnemyAttackState::update_hit_box_pos(Enemy* enemy) {
    CollisionBox* hit_box = enemy->get_hit_box();
    Vector2 size_hit_box = hit_box->get_size();
    Vector2 player_pos = enemy->get_pos();
    float logic_height = enemy->get_logic();
    Vector2 pos_hit_box = player_pos;
    pos_hit_box.y -= logic_height;
    if (!enemy->facing_right()) {
        pos_hit_box.x -= size_hit_box.x;
    }
    hit_box->set_pos(pos_hit_box);
}

void EnemyDeathState::on_enter(Enemy* enemy)
{
    std::string res_name = enemy->get_name() + "_" + "Death";
    enemy->set_animation(res_name);

    Mix_PlayChannel(-1, ResMgr::instance()->find_audio("enemy_death"), 0);
}

void EnemyDeathState::on_exit(Enemy* enemy)
{
    LevelMgr::instance()->destory_enemy(enemy);
}

void EnemyIdleState::on_enter(Enemy* enemy)
{
    std::string res_name = enemy->get_name() + "_" + "Idle";
    enemy->set_animation(res_name);

    timer.set_wait_time(range_randomF(2.0f,4.0f));
    timer.set_one_shot(true);
    timer.set_on_timeout([enemy]() {
        enemy->switch_state("Walk");
        });
    timer.restart();

    enemy->idle();
}

void EnemyIdleState::on_update(Enemy* enemy, float delta)
{
    timer.on_update(delta);
    Vector2 player_pos = LevelMgr::instance()->get_player()->get_pos();

    if (enemy->get_hp() <= 0)
        enemy->switch_state("Death");
    else if (enemy->can_attack(player_pos))
        enemy->switch_state("Attack");
    else if (enemy->can_pursuit(player_pos))
        enemy->switch_state("Pursuit");
}

void EnemyWalkState::on_enter(Enemy* enemy)
{
    std::string res_name = enemy->get_name() + "_" + "Run";
    enemy->set_animation(res_name);

    timer.set_wait_time(range_randomF(0.5f,1.0f));
    timer.set_one_shot(true);
    timer.set_on_timeout([enemy]() {
        enemy->switch_state("Idle");

        SDL_Log("Walk State One Peace !!!");
        });
    timer.restart();

    enemy->walk();

    Mix_PlayChannel(-1, ResMgr::instance()->find_audio("enemy_walk"), 0);
}

void EnemyWalkState::on_update(Enemy* enemy, float delta)
{
    timer.on_update(delta);
    Vector2 player_pos = LevelMgr::instance()->get_player()->get_pos();

    if (enemy->get_hp() <= 0)
        enemy->switch_state("Death");
    else if (enemy->can_attack(player_pos))
        enemy->switch_state("Attack");
    else if(enemy->can_pursuit(player_pos))
        enemy->switch_state("Pursuit");
}

void EnemyWalkState::on_exit(Enemy* enemy) {

}

void EnemyPursuitState::on_enter(Enemy* enemy)
{
    std::string res_name = enemy->get_name() + "_" + "Run";
    enemy->set_animation(res_name);

}

void EnemyPursuitState::on_update(Enemy* enemy, float delta)
{
    Vector2 player_pos = LevelMgr::instance()->get_player()->get_pos();
    enemy->pursuit(player_pos);

    if (enemy->get_hp() <= 0)
        enemy->switch_state("Death");
    else if (enemy->can_attack(player_pos))
        enemy->switch_state("Attack");
    else if (enemy->need_return(player_pos))
        enemy->switch_state("Return");
}

void EnemyPursuitState::on_exit(Enemy* enemy) {
    
}

void EnemyReturnState::on_enter(Enemy* enemy)
{
    std::string res_name = enemy->get_name() + "_" + "Run";
    enemy->set_animation(res_name);

}

void EnemyReturnState::on_update(Enemy* enemy, float delta)
{
    Vector2 player_pos = LevelMgr::instance()->get_player()->get_pos();

    enemy->return_revive();
    if (enemy->get_hp() <= 0)
        enemy->switch_state("Death");
    else if (enemy->can_pursuit(player_pos))
        enemy->switch_state("Pursuit");
    else if (enemy->finish_retrun())
        enemy->switch_state("Idle");

}

void EnemyReturnState::on_exit(Enemy* enemy){

}