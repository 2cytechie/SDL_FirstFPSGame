#pragma once

template <typename T>
class StateNode {
public:
	StateNode() = default;
	~StateNode() = default;

	virtual void on_enter(T* owner) {}
	virtual void on_update(T* owner, float delta) {}
	virtual void on_exit(T* owner) {}

};
