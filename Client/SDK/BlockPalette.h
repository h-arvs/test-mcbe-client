#pragma once

#include "Block.h"
#include <libhat/Access.hpp>
#include <vector>

class BlockPalette {
public:
	std::vector<Block*> getBlocks() {
		return hat::member_at<std::vector<Block*>>(this, 0x68);
	}
};