#pragma once
#include <vector>
#include <functional>

template <class T>
class EventHandler {
public:
	static inline std::vector<std::function<void(T&)>> callbacks{};
	static T trigger() {
		T t;
		for (auto func : EventHandler<T>::callbacks) {
			func(t);
		}
		return t;
	};
};