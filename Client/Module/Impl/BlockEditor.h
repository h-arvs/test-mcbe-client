#pragma once
#include "../Module.h"
#include "../../SDK/Math.h"
class MouseInputEvent;
class RenderEvent;
class HitResult;
class Block;

struct BlockInfo {
	BlockPos mPos;
	Block* mBlock;
	bool selected;

	BlockInfo(BlockPos pos, Block* block) {
		this->mPos = pos;
		this->mBlock = block;
		this->selected = true;
	}

	BlockInfo() {
		this->selected = false;
	}
};

class BlockEditor : public Module {
	HitResult* currentHitResult;
	BlockInfo currentBlock = BlockInfo();
public:
	BlockEditor();
	virtual void onEnable() override;
	virtual void onDisable() override;
	void onMouseInputEvent(MouseInputEvent&);
	void onRender(RenderEvent&);
};