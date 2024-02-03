#include "Jesus.h"
#include "../../Event/Impl/AddShapesEvent.h"
#include "../../Event/Impl/DoInWaterSensingEvent.h"
#include "../../System.h"
#include "../../SDK/Component/Flags/FlagComponent.h"
#include "../../SDK/Component/Flags/InWaterFlag.h"
#include "../../SDK/Component/Flags/ActorHeadInWaterFlag.h"
#include "../../SDK/Component/StateVectorComponent.h"
#include "../../SDK/Component/AABBShapeComponent.h"
#include "../../SDK/LiquidBlock.h"

#include <numeric>

Jesus::Jesus() : Module("Jesus", "Walk on water") {

}

void Jesus::onEnable() {
	this->listen<AddShapesEvent, &Jesus::onAddShapesEvent>();
	this->listen<KeyInputEvent, &Jesus::onKey>();
	this->listen<DoInWaterSensingEvent, &Jesus::onInWaterCheck>();
}

void Jesus::onDisable() {
	this->deafen<AddShapesEvent>();
	this->deafen<KeyInputEvent>();
	this->deafen<DoInWaterSensingEvent>();
}

void Jesus::onKey(KeyInputEvent& e) {
	if (e.getKey() == 16) this->shift = e.getAction();
}

void Jesus::onInWaterCheck(DoInWaterSensingEvent& e) {
	auto p = System::tryGetSystem()->getGame().getClientInstance()->getClientPlayer();
	auto id = p->getEntityContext().id;
	if (id != e.getEntityId()) return;
	e.cancel();
}

void Jesus::onAddShapesEvent(AddShapesEvent& e) {

	auto p = System::tryGetSystem()->getGame().getClientInstance()->getClientPlayer();
	auto ec = p->getEntityContext();

	auto cs = p->getDimension()->getChunkSource();
	if (cs != e.getChunkSource()) return;

	auto sneaking = p->getStatusFlag(ActorFlags::SNEAKING);
	
	auto first = ec.tryGetComponent<AABBShapeComponent>()->aabb.first;
	auto second = ec.tryGetComponent<AABBShapeComponent>()->aabb.second;
	auto under =  Vec3<float>(std::midpoint(first.x, second.x), floor(first.x - 0.1), std::midpoint(first.z, second.z));
	auto bp = static_cast<BlockPos>(under);
	auto bs = p->getDimension()->getBlockSource();
	auto b = bs->getBlock(bp);
	auto m = b->getMaterial();
	auto check = m->isType(MaterialType::Water);
	if (sneaking && check) {
		ec.tryGetComponent<StateVectorComponent>()->velocity.y = -0.2f;
		return;
	}

	if (e.getBlockLegacy()->tileName == "tile.water") {
		auto pos = e.getBlockPos();
		auto a = Vec3<float>(pos);
		auto state = LiquidBlock::getDepth(
			bs,
			pos,
			e.getBlockLegacy()->getMaterial()
			);
		auto depth = LiquidBlock::getHeightFromDepth(state);
		e.addShape(AABB(a, a + Vec3<float>(1, 1 - depth, 1)));
	}
}