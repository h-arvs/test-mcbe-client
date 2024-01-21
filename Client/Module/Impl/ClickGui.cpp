#include "ClickGui.h"
#include "../../Event/Impl/RenderEvent.h"
#include "../../Event/Impl/KeyInputEvent.h"
#include "../../Event/Impl/MouseInputEvent.h"
#include <imgui.h>
#include "../../System.h"

ClickGui::ClickGui() : Module("ClickGui", "Clickable gui to interact with modules") {
	this->bind(45);
}

void ClickGui::onEnable() {
	this->listen<RenderEvent, &ClickGui::onRender>();
	this->listen<KeyInputEvent, &ClickGui::onKey>();
	this->listen<MouseInputEvent, &ClickGui::onMouse>();
	System::tryGetSystem()->getGame().getClientInstance()->acquireCursor();
}

void ClickGui::onDisable() {
	this->deafen<RenderEvent>();
	this->deafenSingle<KeyInputEvent, &ClickGui::onKey>();
	this->deafen<MouseInputEvent>();

	System::tryGetSystem()->getGame().getClientInstance()->dropCursor();
}

void ClickGui::onKey(KeyInputEvent& e) {
	e.cancel();
}

void ClickGui::onMouse(MouseInputEvent& e) {
	e.cancel();
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