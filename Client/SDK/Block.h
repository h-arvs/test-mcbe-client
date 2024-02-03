#pragma once
#include "BlockLegacy.h"

class Block {
public:
	BlockLegacy* getBlockLegacy() {
		return hat::member_at<BlockLegacy*>(this, 0x30);
	}

	Material* getMaterial() {
		return this->getBlockLegacy()->getMaterial();
	}
};