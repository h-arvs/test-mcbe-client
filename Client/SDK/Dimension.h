#pragma once

#include "BlockSource.h"

class Dimension {
public:
	DIRECT_ACCESS(BlockSource*, blockSource, 0xD0);
	DIRECT_ACCESS(ChunkSource*, chunkSource, 0x198);
};