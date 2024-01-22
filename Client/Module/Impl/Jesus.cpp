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
		auto a = e.getBlockPos();
		e.addShape(AABB(a.x, a.y, a.z, a.x + 1, a.y + 1, a.z + 1));
	}
}