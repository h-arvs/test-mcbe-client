#pragma once
#include <functional>
#include "EventHandler.h"

class Listener {
public:
	template<class Event, auto callback, typename Self> void listen(this Self& self) {
		EventHandler::dispatcher.sink<Event>().connect<callback>(&self);
	}

	template<class Event, typename Self> void deafen(this Self& self) {
		EventHandler::dispatcher.sink<Event>().disconnect(&self);
	}
};
