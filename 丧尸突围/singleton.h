#pragma once

template <typename T>
class Singleton {
public:
	static T* instance() {
		if (!_instance) {
			_instance = new T();
		}
		return _instance;
	}
private:
	static T* _instance;
protected:
	Singleton() = default;
	virtual ~Singleton() = default;
};

template <typename T>
T* Singleton<T>::_instance = nullptr;