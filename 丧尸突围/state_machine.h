#pragma once

#include "state_node.h"

#include<string>
#include<graphics.h>
#include<unordered_map>

class StateMachine {
public:
	StateMachine();
	~StateMachine();

	void on_update(float delta);

	void set_entry(const std::string& id);									// 状态机初始状态
	void switch_state(const std::string& id);								// 切换状态机
	void register_state(const std::string& id, StateNode* state_node);		// 向状态机中注册新的状态

private:
	bool need_init = true;													// 当前状态机是否被初始化
	StateNode* current_state = nullptr;										// 当前状态机指针
	std::unordered_map<std::string, StateNode*> state_pool;
};