#include "CommandManager.h"
#include "Impl/PingCommand.h"
#include "Impl/HiCommand.h"
#include "../System.h"
#include "Impl/CommandInstanceComponent.h"

CommandManager::CommandManager(){
	this->addCommands<
		PingCommand,
		HiCommand
	>();
}

template<class T>
bool CommandManager::addCommand() {
	auto command = this->commands.create();
	this->commands.emplace<CommandInstanceComponent>(command, std::make_unique<T>());
	return true;
}

template <class... Ts>
void CommandManager::addCommands() {
	(this->addCommand<Ts>(), ...);
}
void CommandManager::executeCommand(std::string rawCommandString) {
	auto a = rawCommandString;
	a.erase(0, this->commandPrefix.length());
	auto splitArgs = std::vector<std::string>();
	std::string hold = " ";
	a += hold;
	auto pos = 0;

	while ((pos = a.find(" ")) != std::string::npos) {
		splitArgs.push_back(a.substr(0, pos));	
		a.erase(0, pos + hold.length());
	}

	for (auto [e, c] : this->commands.view<CommandInstanceComponent>().each()) {
		auto& instance = c.instance;
		if (instance->getName().rfind(splitArgs.at(0)) == 0) {
			splitArgs.erase(splitArgs.begin()); // remove command name from arg list
			return instance->execute(splitArgs);
		}
	}

	auto msg = "No command found with name " + splitArgs.at(0);
	return this->reply(msg);
}

void CommandManager::reply(std::string& msg) {
	System::tryGetSystem()->getGame().getClientInstance()->getGuiData()->displayMessage(msg);
}

