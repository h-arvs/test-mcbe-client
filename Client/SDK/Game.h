#pragma once
#include "ClientInstance.h"

class Game {
	ClientInstance* clientInstance = nullptr;
public:
	ClientInstance* getClientInstance();
	void setClientInstance(ClientInstance*);
};