#include "AddShapesHook.h"
#include "../../SDK/BlockLegacy.h"
#include "../../SDK/Math.h"
#include "../../Event/EventHandler.h"
#include "../../Event/Impl/AddShapesEvent.h"

class Block;
class BlockSource;

bool(_fastcall* AddShapesO)(BlockLegacy* self, Block& block, BlockSource& blocksource, BlockPos& blockpos, AABB* aabb, std::vector<AABB>& aabbs, void* arg7);
bool(__fastcall AddShapesCallback)(BlockLegacy* self, Block& block, BlockSource& blocksource, BlockPos& blockpos, AABB* aabb, std::vector<AABB>& aabbs, void* arg7) {
	auto result = AddShapesO(self, block, blocksource, blockpos, aabb, aabbs, arg7);
	auto e = AddShapesEvent(aabbs, self, aabb, blockpos);
	EventHandler<AddShapesEvent>::trigger(e);
	aabbs = e.getShapes();
	return result;
}

void AddShapesHook::patch() {
	this->autoPatch("40 53 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 48 8B 01 4D 8B D1",
		&AddShapesCallback,
		&AddShapesO
	);
}

