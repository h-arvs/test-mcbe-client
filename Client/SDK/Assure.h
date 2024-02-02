#pragma once
#include "EntityId.h"
#include <entt/entity/registry.hpp>

namespace Assure {
	template<typename component_t>
	auto& assure_for(entt::basic_registry<EntityId>* registry)
	{
		return registry->storage<component_t>();
	}
}