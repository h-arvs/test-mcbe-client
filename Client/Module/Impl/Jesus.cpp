#include "Jesus.h"
#include "../../Event/Impl/AddShapesEvent.h"
#include "../../Event/Impl/DoInWaterSensingEvent.h"
#include "../../System.h"
#include "../../SDK/Component/Flags/FlagComponent.h"
#include "../../SDK/Component/Flags/InWaterFlag.h"
#include "../../SDK/Component/Flags/ActorHeadInWaterFlag.h"
#include "../../SDK/Component/StateVectorComponent.h"
#include "../../SDK/Component/AABBShapeComponent.h"
#include "../../SDK/Component/MoveInputComponent.h"
#include "../../SDK/LiquidBlock.h"

#include <numeric>

Jesus::Jesus() : Module("Jesus", "Walk on water") {

}

void Jesus::onEnable() {
	this->listen<AddShapesEvent, &Jesus::onAddShapesEvent>();
	this->listen<DoInWaterSensingEvent, &Jesus::onInWaterCheck>();
}

void Jesus::onDisable() {
	this->deafen<AddShapesEvent>();
	this->deafen<DoInWaterSensingEvent>();
}


void Jesus::onInWaterCheck(DoInWaterSensingEvent& e) {
	auto p = System::tryGetSystem()->getGame().getClientInstance()->getClientPlayer();
	auto ec = p->getEntityContext();
	if (ec.id != e.getEntityId()) return;
	if (ec.tryGetComponent<MoveInputComponent>()->mWantDown || ec.hasComponent<FlagComponent<InWaterFlag>>()) return;
	e.cancel();
}

void Jesus::onAddShapesEvent(AddShapesEvent& e) {

	auto p = System::tryGetSystem()->getGame().getClientInstance()->getClientPlayer();
	auto ec = p->getEntityContext();

	auto cs = p->getDimension()->getChunkSource();
	if (cs != e.getChunkSource()) return;
	
	auto first = ec.tryGetComponent<AABBShapeComponent>()->aabb.first;
	auto playerpos = ec.tryGetComponent<StateVectorComponent>()->currentPos;
	auto bottom = static_cast<BlockPos>(Vec3<float>(floor(playerpos.x), first.y, playerpos.z));
	auto under = static_cast<BlockPos>(Vec3<float>(floor(playerpos.x), floor(first.y - 0.2), playerpos.z));
	auto bs = p->getDimension()->getBlockSource();
	auto b = bs->getLiquidBlock(under);

	if (ec.tryGetComponent<MoveInputComponent>()->mWantDown && b->getMaterial()->isType(MaterialType::Water)) {
		ec.tryGetComponent<StateVectorComponent>()->velocity.y = -0.2f;
		return;
	}

	if (ec.hasComponent<FlagComponent<InWaterFlag>>()) return;


	auto pos = e.getBlockPos();
	auto liquidblock = bs->getLiquidBlock(pos);
	if (liquidblock->getMaterial()->isType(MaterialType::Water)) {
		auto a = Vec3<float>(pos);
		auto state = LiquidBlock::getDepth(
			bs,
			pos,
			liquidblock->getMaterial()
			);
		auto depth = LiquidBlock::getHeightFromDepth(state);
		e.addShape(AABB(a, a + Vec3<float>(1, 1 - depth, 1)));
	}
}