#pragma once
#include <vector>
#include <functional>
#include <entt/entt.hpp>

template <class T>
class EventHandler {
public:
	static inline entt::sigh<void(T&)> signal;
	static inline entt::sink sink{ signal };
	static void trigger(T& e) {
		EventHandler<T>::signal.publish(e);
	}
};