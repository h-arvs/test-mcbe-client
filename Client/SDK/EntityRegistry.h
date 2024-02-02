// 100 percent from nuvola again ima skidd

#pragma once
#include "EntityId.h"
#include <entt/entt.hpp>

class EntityRegistryBase
{
public:
	entt::basic_registry<EntityId>* mEnttRegistry = nullptr;
	EntityRegistryBase* mRegistry = nullptr;
};

class EntityRegistry : public EntityRegistryBase {
public:
	std::string mName;
	entt::basic_registry<EntityId> mOwnedRegistry;
};