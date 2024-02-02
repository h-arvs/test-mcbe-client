#include "Jesus.h"
#include "../../Event/Impl/AddShapesEvent.h"
#include "../../System.h"
#include "../../SDK/Component/Flags/FlagComponent.h"
#include "../../SDK/Component/Flags/InWaterFlag.h"
#include "../../SDK/Component/StateVectorComponent.h"
#include "../../SDK/LiquidBlock.h"

Jesus::Jesus() : Module("Jesus", "Walk on water") {

}

void Jesus::onEnable() {
	this->listen<AddShapesEvent, &Jesus::onAddShapesEvent>();
	this->listen<KeyInputEvent, &Jesus::onKey>();
}

void Jesus::onDisable() {
	this->deafen<AddShapesEvent>();
	this->deafen<KeyInputEvent>();
}

void Jesus::onKey(KeyInputEvent& e) {
	if (e.getKey() == 16) this->shift = e.getAction();
}

void Jesus::onAddShapesEvent(AddShapesEvent& e) {

	auto p = System::tryGetSystem()->getGame().getClientInstance()->getClientPlayer();
	auto ec = p->getEntityContext();

	auto cs = p->getDimension()->getChunkSource();
	if (cs != e.getChunkSource()) return;

	auto sneaking = this->shift == Action::PRESSED;
	if (ec.hasComponent<FlagComponent<InWaterFlag>>() && !sneaking) 
	{
		auto v = ec.tryGetComponent<StateVectorComponent>();
		v->velocity.y = 0.2f;
		return;
	}
	
	if (sneaking) {
		auto v = ec.tryGetComponent<StateVectorComponent>();
		v->velocity.y = -0.2f;
		return;
	}

	if (e.getBlockLegacy()->tileName == "tile.water") {
		auto pos = e.getBlockPos();
		auto a = Vec3<float>(pos);
		auto state = LiquidBlock::getDepth(
			p->getDimension()->getBlockSource(),
			pos,
			e.getBlockLegacy()->getMaterial()
			);
		auto depth = LiquidBlock::getHeightFromDepth(state);
		e.addShape(AABB(a, a + Vec3<float>(1, depth, 1)));
	}
}