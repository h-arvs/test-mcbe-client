#pragma once

class ClientInstance;
class Game {
	ClientInstance* clientInstance = nullptr;
public:
	ClientInstance* getClientInstance();
	void setClientInstance(ClientInstance*);
};