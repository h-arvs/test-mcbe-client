#include "BlockEditor.h"
#include "../../System.h"
#include "../../Event/Impl/MouseInputEvent.h"
#include "../../Event/Impl/RenderEvent.h"
#include "../../Event/EventHandler.h"
#include <ImGui.h>
#include <iomanip>
#include <iostream>
#include <sstream>

BlockEditor::BlockEditor() : Module("Block Editor", "Select blocks and edit them!") {
}

void BlockEditor::onEnable() {
	this->currentHitResult = System::tryGetSystem()->getGame().getClientInstance()->getClientPlayer()->getLevel()->getHitResult();
	this->listen<RenderEvent, &BlockEditor::onRender>();
	this->listen<MouseInputEvent, &BlockEditor::onMouseInputEvent>();
}

void BlockEditor::onDisable() {
	this->deafen<RenderEvent>();
	this->deafen<MouseInputEvent>();
}

void BlockEditor::onMouseInputEvent(MouseInputEvent& e) {
	if (e.getButton() == MouseButton::Middle && e.getAction() == MouseAction::Press) {
		e.cancel();
		auto bp = this->currentHitResult->mBlockPos;
		auto block = System::tryGetSystem()->getGame().getClientInstance()->getClientPlayer()->getDimension()->getBlockSource()->getBlock(bp);
		this->currentBlock = BlockInfo(bp, block);
	}
}

void BlockEditor::onRender(RenderEvent& e) {
	ImGui::Begin("Selected Block");
	if (this->currentBlock.selected) {
		ImGui::Text("Tile name: %s", this->currentBlock.mBlock->getBlockLegacy()->tileName.c_str());
		ImGui::Text("x; %d, y: %d, z: %d", this->currentBlock.mPos.x, this->currentBlock.mPos.y, this->currentBlock.mPos.z);
	}
	else {
		ImGui::Text("No Block Selected, midclick to select a block");
	}
	ImGui::End();
}