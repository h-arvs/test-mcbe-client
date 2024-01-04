#include "Game.h"
#include "../Event/Impl/CIUpdateEvent.h"

Game::Game() {
	this->listen<ClientInstanceUpdateEvent, &Game::onCIUpdate>();
}

ClientInstance* Game::getClientInstance() {
	return this->clientInstance;
}

void Game::onCIUpdate(ClientInstanceUpdateEvent& event) {
	this->clientInstance = event.getClientInstance();
}