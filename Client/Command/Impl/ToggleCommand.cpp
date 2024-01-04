#include "ToggleCommand.h"
#include "../../System.h"

ToggleCommand::ToggleCommand() : Command({ "t", "toggle" }, "Toggles a module") {
}

void ToggleCommand::execute(std::vector<std::string> args) {
	std::string fullName = "";

	int thing = 0;
	for (std::string param : args) {
		thing = thing + 1;
		std::string thing2 = args.size() == thing ? "" : " ";
		fullName = fullName + param + thing2;
	}
	auto mod = System::tryGetSystem()->getModuleManager().get(fullName);
	if (mod != nullptr) {
		auto state = mod->toggle();
		return this->reply(state ? "Toggled " + args[0] + " on" : "Toggled " + args[0] + " off");
	}
	return this->reply("Module '" + fullName + "' not found");
}