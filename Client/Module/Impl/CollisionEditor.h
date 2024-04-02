#pragma once
#include "../Module.h"
#include "../../SDK/Math.h"

class ClientInstanceUpdateEvent;
class RenderEvent;
class Block;
class BlockPalette;
class AddShapesEvent;

class CollisionEditor : public Module {
public:
	CollisionEditor();
	void onEnable() override;
	void onDisable() override; 
	void onRender(RenderEvent&);
	void onAddShapesEvent(AddShapesEvent& e);

	BlockPalette* blockPalette;
	std::unordered_map<std::string, bool> map;
	std::unordered_map<std::string, int> indexLookupMap;
	std::unordered_map<std::string, AABB> aabbLookupMap;
};