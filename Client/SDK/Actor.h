#pragma once

#include "macros.h"
#include "Dimension.h"
#include "EntityContext.h"
#include <libhat/Access.hpp>
#include "Component/StateVectorComponent.h"
#include "SynchedActorDataEntityWrapper.h"

class Actor {
public:
	EntityContext& getEntityContext() {
		return hat::member_at<EntityContext>(this, 0x8);
	}

	Dimension* getDimension() {
		return hat::member_at<Dimension*>(this, 0x278);
	}

	StateVectorComponent* getStateVectorComponent() {
		return hat::member_at<StateVectorComponent*>(this, 0x2C8);
	}

	SynchedActorDataEntityWrapper* getSynchedActorDataEntityWrapper() {
		return hat::member_at<SynchedActorDataEntityWrapper*>(this, 0x190);
	}

	virtual bool getStatusFlag(ActorFlags);
};