#pragma once
#include "WeakRef.h"
#include "EntityContext.h"

struct WeakEntityRef {
	WeakRef<EntityContext> mWeakEntity;
};