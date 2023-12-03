#include "Game.h"

ClientInstance* Game::getClientInstance() {
	return this->clientInstance;
}

void Game::setClientInstance(ClientInstance* ptr) {
	this->clientInstance = ptr;
}