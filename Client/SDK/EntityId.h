// also from nuvola

#pragma once

#ifdef ENTT_ENTITY_FWD_HPP
static_assert(false, "Please include EntityId.h before all entt headers!");
#endif

#include "entt/fwd.hpp"

#include <cstdint>
enum class EntityId : std::uint32_t {};

#include <entt/entity/entity.hpp>

#include <memory>

template<>
struct entt::internal::entt_traits<EntityId> {
	using value_type = EntityId;

	using entity_type = std::uint32_t;
	using version_type = std::uint16_t;

	static constexpr entity_type entity_mask = 0x3FFFF;
	static constexpr entity_type version_mask = 0x3FFF;
};