#pragma once

#include <libhat/Access.hpp>
#include "ChunkSource.h"
#include "macros.h"

class BlockSource {
public:
	ChunkSource* getChunkSource() {
		return hat::member_at<ChunkSource*>(this, 0x28);
	}
};