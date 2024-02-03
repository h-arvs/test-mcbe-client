#pragma once

#include "Cancellable.h"
#include "../../SDK/ChunkSource.h"
#include "../../SDK/EntityId.h"

class DoInWaterSensingEvent : public Cancellable{
	EntityId entityId;
public:
	DoInWaterSensingEvent(EntityId entityId) {
		this->entityId = entityId;
	}

	EntityId getEntityId() {
		return this->entityId;
	}
};