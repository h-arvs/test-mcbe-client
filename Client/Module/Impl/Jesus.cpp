#include "Jesus.h"
#include "../../Event/Impl/AddShapesEvent.h"

Jesus::Jesus() : Module("Jesus", "Walk on water") {

}

void Jesus::onEnable() {
	this->listen<AddShapesEvent, &Jesus::onAddShapesEvent>();
}

void Jesus::onDisable() {
	this->deafen<AddShapesEvent>();
}

void Jesus::onAddShapesEvent(AddShapesEvent& e) {
	if (e.getBlock()->tileName == "tile.water") {
		auto a = Vec3<float>(e.getBlockPos());
		e.addShape(AABB(a, a + Vec3<float>(1, 1, 1)));
	}
}