#pragma once
#include <string>
#include <libhat/Access.hpp>
#include "Material.h"
#include "macros.h"

#include "Math.h"

class Block;
class BlockSource;
class BlockPos;

class BlockLegacy {
public:
	char pad_0008[32];
	std::string tileName;

	Material* getMaterial() {
		return hat::member_at<Material*>(this, 0x128);
	}

	AABB getCollisionShape(Block* block, BlockSource* blockSource, BlockPos* blockPos) {
		return vftCall<5, AABB, Block*, BlockSource*, BlockPos*, void*>(this, block, blockSource, blockPos, 0);
	}

	virtual ~BlockLegacy() = default;
};