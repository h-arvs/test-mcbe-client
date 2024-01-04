#pragma once

#include "../../SDK/ClientInstance.h"

class ClientInstanceUpdateEvent {
	ClientInstance* ci;
public:
	ClientInstanceUpdateEvent(ClientInstance* ci) {
		this->ci = ci;
	}
	
	ClientInstance* getClientInstance(){
		return this->ci;
	}
};