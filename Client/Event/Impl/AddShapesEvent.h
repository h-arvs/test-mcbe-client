#pragma once
#include <vector>
#include "../../SDK/Math.h"
#include "../../SDK/BlockLegacy.h"

class AddShapesEvent {
	std::vector<AABB> shapes;
	BlockLegacy* block;
	AABB* entityAABB;
	BlockPos pos;
public:
	AddShapesEvent(std::vector<AABB> aabbs, BlockLegacy* block, AABB* entity, BlockPos pos) {
		this->shapes = aabbs;
		this->block = block;
		this->entityAABB = entity;
		this->pos = pos;
	}

	std::vector<AABB> getShapes() {
		return this->shapes;
	}

	void addShape(AABB aabb) {
		this->shapes.push_back(aabb);
	}

	BlockLegacy* getBlock() {
		return this->block;
	}

	AABB* getEntityAABB() {
		return this->entityAABB;
	}

	BlockPos getBlockPos() {
		return this->pos;
	}
};