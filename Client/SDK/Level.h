#pragma once
#include <libhat/Access.hpp>
#include "BlockPalette.h"
#include "HitResult.h"

class Level {
public:
	BlockPalette* getBlockPallete() {
		return hat::member_at<BlockPalette*>(this, 0xAC0);
	}

	HitResult* getHitResult() {
		return hat::member_at<HitResult*>(this, 0xB30);
	}
};