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
	this->deafen<KeyInputEvent>();
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
	auto window = ImGui::GetBackgroundDrawList();
	auto size = ImGui::GetIO().DisplaySize;
	//window->AddRectFilled(ImVec2(0, 0), size, IM_COL32(0, 0, 0, 128));
	ImGui::SetNextWindowSize(ImVec2(700, 500));
	ImGui::Begin("Click Gui", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
	for (auto& catagory : System::tryGetSystem()->getModuleManager().items) {
		ImGui::Text(catagory->getName().c_str());
		ImGui::NewLine();
		for (auto& mod : catagory->items) {
			ImGui::SameLine();
			if(mod->enabled)
			{
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 1.0f, 0.0f, 1.0f));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.5f, 1.0f, 0.5f, 1.0f));
			}
			else 
			{
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.5f, 0.5f, 1.0f));	
			}				
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 1.0f, 1.0f));
			if (ImGui::Button(mod->name.c_str())) {
				mod->toggle();
			};
			ImGui::PopStyleColor(3);
		}
	}
	ImGui::End();
}