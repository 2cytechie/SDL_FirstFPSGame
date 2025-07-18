#include "state_machine.h"

template <typename T>
void StateMachine<T>::on_update(float delta) {
	if (!current_state) return;

	if (need_init) {
		current_state->on_enter(owner);
		need_init = false;
	}
	current_state->on_update(owner, delta);
}

template <typename T>
void StateMachine<T>::set_entry(const std::string& id) {
	current_state = state_pool[id];
}

template <typename T>
void StateMachine<T>::switch_state(const std::string& id) {
	if (current_state) current_state->on_exit(owner);
	current_state = state_pool[id];
	if (current_state) current_state->on_enter(owner);
}

template <typename T>
void StateMachine<T>::register_state(T* owner, const std::string& id, StateNode<T>* state_node) {
	this->owner = owner;
	state_pool[id] = state_node;
}