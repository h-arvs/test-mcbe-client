#pragma once
#include "ClientInstance.h"
#include "../Event/Listener.h"

class ClientInstanceUpdateEvent;

class Game : public Listener{
	ClientInstance* clientInstance = nullptr;
public:
	Game();
	ClientInstance* getClientInstance();
	void onCIUpdate(ClientInstanceUpdateEvent&);
};