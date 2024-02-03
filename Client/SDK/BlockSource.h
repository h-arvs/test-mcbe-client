#pragma once

#include <libhat/Access.hpp>
#include "ChunkSource.h"
#include "Math.h"
#include "Block.h"
#include "macros.h"

class BlockSource {
public:
	ChunkSource* getChunkSource() {
		return hat::member_at<ChunkSource*>(this, 0x28);
	}

	Block* getBlock(BlockPos& blockPos) {
		return vftCall<2, Block*, BlockPos&>(this, blockPos);
	}
};