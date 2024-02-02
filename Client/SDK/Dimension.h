#pragma once

#include "BlockSource.h"

class Dimension {
public:
	BlockSource* getBlockSource() {
		return hat::member_at<BlockSource*>(this, 0xD0);
	}

	ChunkSource* getChunkSource() {
		return hat::member_at<ChunkSource*>(this, 0x198);
	}
};