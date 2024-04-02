#include "CollisionEditor.h"
#include "../../Event/Impl/CIUpdateEvent.h"

#include "../../System.h"
#include "../../Event/Impl/RenderEvent.h"
#include "../../Event/Impl/AddShapesEvent.h"
#include "../../SDK/BlockPalette.h"

#include <imgui.h>
#include <fstream>

CollisionEditor::CollisionEditor() : Module("Collision Editor", "Edit the aabbs on blocks") {
}

void CollisionEditor::onEnable() {
	this->listen<RenderEvent, &CollisionEditor::onRender>();
	this->listen<AddShapesEvent, &CollisionEditor::onAddShapesEvent>();
	this->blockPalette = System::tryGetSystem()->getGame().getClientInstance()->getClientPlayer()->getLevel()->getBlockPallete();
	for (int i = 0; i < this->blockPalette->getBlocks().size(); ++i) {
		auto block = this->blockPalette->getBlocks()[i];
		if (this->map.find(block->getBlockLegacy()->tileName) == this->map.end()) {
			this->map.emplace(block->getBlockLegacy()->tileName, false);
			this->indexLookupMap.emplace(block->getBlockLegacy()->tileName, i);
		}
	}
}

void CollisionEditor::onDisable() {
	this->deafen<RenderEvent>();
	this->deafen<AddShapesEvent>();
}

void CollisionEditor::onAddShapesEvent(AddShapesEvent& e) {
	if (this->aabbLookupMap.find(e.getBlockLegacy()->tileName) != this->aabbLookupMap.end()) {
		e.clearShapes();
		auto custom = this->aabbLookupMap.at(e.getBlockLegacy()->tileName);
		auto cast = static_cast<Vec3<int>>(e.getBlockPos());
		e.addShape(AABB(cast + custom.first, cast + custom.second));
	}
}

void CollisionEditor::onRender(RenderEvent& e) {
	ImGui::Begin("BlockSelection");
	for (auto& name : this->map) {
		ImGui::Checkbox(name.first.c_str(), &name.second);
		if (name.second) {
			if (this->aabbLookupMap.find(name.first) == this->aabbLookupMap.end()) {
				this->aabbLookupMap.emplace(name.first, AABB(0, 0, 0, 1, 1, 1));
			}
			ImGui::SliderFloat("First x", &this->aabbLookupMap.at(name.first).first.x, 0, 2);
			ImGui::SliderFloat("Second x", &this->aabbLookupMap.at(name.first).second.x, 0, 2);
			ImGui::SliderFloat("First z", &this->aabbLookupMap.at(name.first).first.z, 0, 2);
			ImGui::SliderFloat("Second z", &this->aabbLookupMap.at(name.first).second.z, 0, 2);
			ImGui::SliderFloat("First Y", &this->aabbLookupMap.at(name.first).first.y, 0, 2);
			ImGui::SliderFloat("Second y", &this->aabbLookupMap.at(name.first).second.y, 0, 2);
		}
		else if (this->aabbLookupMap.find(name.first) != this->aabbLookupMap.end()) {
			this->aabbLookupMap.erase(name.first);
		}
	}
	ImGui::End();
}