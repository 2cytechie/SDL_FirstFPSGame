#pragma once

#include "state_node.h"
#include <string>
#include <unordered_map>

extern bool DEBUG;

template <typename T>
class StateMachine {
public:
    StateMachine() = default;
    ~StateMachine() = default;

    void on_update(float delta) {
        if (!current_state) return;

        if (need_init) {
            current_state->on_enter(owner);
            need_init = false;
        }
        current_state->on_update(owner, delta);
    }

    void set_entry(const std::string& id) {
        current_state = state_pool[id];
    }

    void switch_state(const std::string& id) {
        std::string debug = id;
        SDL_Log(("current_state:    " + debug).c_str());

        if (current_state) current_state->on_exit(owner);
        current_state = state_pool[id];
        if (current_state) current_state->on_enter(owner);
    }

    void register_state(T* owner, const std::string& id, StateNode<T>* state_node) {
        this->owner = owner;
        state_pool[id] = state_node;
    }

private:
    T* owner;
    bool need_init = true;
    StateNode<T>* current_state = nullptr;
    std::unordered_map<std::string, StateNode<T>*> state_pool;
};