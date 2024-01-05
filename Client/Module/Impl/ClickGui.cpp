#include "ClickGui.h"
#include "../../Event/Impl/RenderEvent.h"
#include <imgui.h>

ClickGui::ClickGui() : Module("ClickGui", "Clickable gui to interact with modules") {
}

void ClickGui::onEnable() {
	this->listen<RenderEvent, &ClickGui::onRender>();
}

void ClickGui::onDisable() {
	this->deafen<RenderEvent>();
}

void ClickGui::onRender(RenderEvent&) {
	ImGui::ShowDemoWindow();
}