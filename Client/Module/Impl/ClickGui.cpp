#include "ClickGui.h"
#include "../../Event/Impl/RenderEvent.h"
#include <imgui.h>
#include "../../System.h"

ClickGui::ClickGui() : Module("ClickGui", "Clickable gui to interact with modules") {
}

void ClickGui::onEnable() {
	this->listen<RenderEvent, &ClickGui::onRender>();
}

void ClickGui::onDisable() {
	this->deafen<RenderEvent>();
}

void ClickGui::onRender(RenderEvent&) {
	for (auto& catagory : System::tryGetSystem()->getModuleManager().items) {
		ImGui::Begin(catagory->getName().c_str());
		for (auto& mod : catagory->items) {
			ImGui::Button(mod->name.c_str());
		}
		ImGui::End();
	}
}