#pragma once
#include <string>
#include <libhat/Access.hpp>
#include "Material.h"

class BlockLegacy {
public:
	char pad_0008[32];
	std::string tileName;

	Material* getMaterial() {
		return hat::member_at<Material*>(this, 0x128);
	}
	virtual ~BlockLegacy() = default;
};