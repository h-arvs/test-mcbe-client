#pragma once

#include "macros.h"
#include "Dimension.h"
#include "EntityContext.h"
#include <libhat/Access.hpp>
#include "Component/StateVectorComponent.h"
#include "Component/AABBShapeComponent.h"
#include "SynchedActorDataEntityWrapper.h"
#include "Level.h"

class Actor {
public:
	EntityContext& getEntityContext() {
		return hat::member_at<EntityContext>(this, 0x8);
	}

	Dimension* getDimension() {
		return hat::member_at<Dimension*>(this, 0x240);
	}

	StateVectorComponent* getStateVectorComponent() {
		return hat::member_at<StateVectorComponent*>(this, 0x298);
	}

	BlockPos getBlockPosCurrentlyStandingOn() {
		auto ec = this->getEntityContext();
		auto pos = ec.tryGetComponent<StateVectorComponent>()->currentPos;
		auto aabb = ec.tryGetComponent<AABBShapeComponent>()->aabb;
		using func = BlockPos(__fastcall*)(Vec3<float>*, AABB, BlockSource*, int64_t);
		static func _func = (func)(Mem::FindSig("48 89 5C 24 ? 57 48 83 EC ? 49 8B 01 4D 8B D9"));
		return _func(&pos, aabb, this->getDimension()->getBlockSource(), 0);
	}

	Level* getLevel() {
		return hat::member_at<Level*>(this, 0x258);
	}

	virtual bool getStatusFlag(ActorFlags);
};