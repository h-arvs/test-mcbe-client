#pragma once
#include <functional>
#include "EventHandler.h"

class Listener {
public:
	template <class Event, auto Callback> void listen(auto* self) {
		EventHandler<Event>::callbacks.push_back([self](Event& e) {(self->*Callback)(e);});
	};
};
