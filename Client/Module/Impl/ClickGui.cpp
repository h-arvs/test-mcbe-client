#include "ClickGui.h"
#include "../../Event/Impl/RenderEvent.h"
#include <imgui.h>
#include "../../System.h"

ClickGui::ClickGui() : Module("ClickGui", "Clickable gui to interact with modules") {
	this->bind(45);
}

void ClickGui::onEnable() {
	this->listen<RenderEvent, &ClickGui::onRender>();
}

void ClickGui::onDisable() {
	this->deafen<RenderEvent>();
}

void ClickGui::onRender(RenderEvent&) {
	ImGui::SetNextWindowSize(ImVec2(700, 500));
	ImGui::Begin("Click Gui", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
	int id = 1;
	for (auto& catagory : System::tryGetSystem()->getModuleManager().items) {
		ImGui::Button(catagory->getName().c_str());
		ImGui::BeginChild(id);
		for (auto& mod : catagory->items) {
			ImGui::Button(mod->name.c_str());
		}
		ImGui::EndChild();
		id += 1;
	}
	ImGui::End();
}