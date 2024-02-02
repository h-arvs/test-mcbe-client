#pragma once
#include <vector>
#include "../../SDK/Math.h"
#include "../../SDK/BlockLegacy.h"
#include "../../SDK/Block.h"
#include "../../SDK/ChunkSource.h"

class AddShapesEvent {
	std::vector<AABB> shapes;
	BlockLegacy* blockLegacy;
	Block* block;
	ChunkSource* chunkSource;
	BlockPos pos;
public:
	AddShapesEvent(std::vector<AABB> aabbs, BlockLegacy* blockLegacy, ChunkSource* chunkSource, BlockPos pos, Block* block) {
		this->shapes = aabbs;
		this->blockLegacy = blockLegacy;
		this->pos = pos;
		this->chunkSource = chunkSource;
		this->block = block;
	}

	std::vector<AABB> getShapes() {
		return this->shapes;
	}

	void addShape(AABB aabb) {
		this->shapes.push_back(aabb);
	}

	BlockLegacy* getBlockLegacy() {
		return this->blockLegacy;
	}

	Block* getBlock() {
		return this->block;
	}

	BlockPos getBlockPos() {
		return this->pos;
	}

	ChunkSource* getChunkSource() {
		return this->chunkSource;
	}
};