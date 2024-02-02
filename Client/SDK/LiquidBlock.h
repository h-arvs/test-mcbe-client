#pragma once

#include "Block.h"
#include "BlockSource.h"
#include "Math.h"
#include "../../Utils/Mem.h"

class LiquidBlock : public Block {
public:
	static int64_t getDepth(BlockSource* bs, BlockPos& bp, Material* m) {
		static auto sig = Mem::FindSig("40 53 48 83 EC 20 48 8B 01 49 8B D8 48 8B 40 30 FF 15");
		using func = int64_t(__fastcall*)(BlockSource*, BlockPos&, Material*);
		func _func = (func)sig;
		return _func(bs, bp, m);
	}

	static float getHeightFromDepth(int64_t depth) {
		auto a = 0;
		if (depth < 8) a = depth;
		return (a + 1) * 0.11111111f;
	}
};