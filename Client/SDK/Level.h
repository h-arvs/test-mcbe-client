#pragma once
#include <libhat/Access.hpp>
#include "BlockPalette.h"

class Level {
public:
	BlockPalette* getBlockPallete() {
		return hat::member_at<BlockPalette*>(this, 0xA28);
	}
};