#include "CommandManager.h"
#include "Impl/PingCommand.h"
#include "Impl/HiCommand.h"
#include "Impl/ToggleCommand.h"
#include "../System.h"
#include "../Event/Impl/PacketSendEvent.h"
#include "../SDK/TextPacket.h"

CommandManager::CommandManager(){
	this->listen<PacketSendEvent, &CommandManager::onPacketSend>();
	this->addItems<
		PingCommand,
		HiCommand,
		ToggleCommand
	>();
}

Command* CommandManager::findCommand(std::string name) {
	for (auto& instance : this->items) {
		for (auto n : instance->names) {
			if (n == name) {
				return instance.get();
			}
		}
	}
	return nullptr;
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

	auto instance = this->findCommand(splitArgs.at(0));
	if (instance != nullptr) {
		splitArgs.erase(splitArgs.begin()); // remove command name from arg list
		return instance->execute(splitArgs);
	}
	
	auto msg = "Command not found with name " + splitArgs.at(0);
	this->reply(msg);
}

void CommandManager::reply(std::string& msg) {
	System::tryGetSystem()->getGame().getClientInstance()->getGuiData()->displayMessage(msg);
}

void CommandManager::onPacketSend(PacketSendEvent& event) {
	auto a = event.getPacket()->getId();
	if (a == PacketID::TextPacket) {
		auto b = reinterpret_cast<TextPacket*>(event.getPacket());
		auto& cm = System::tryGetSystem()->getCommandManager();
		if (b->text.starts_with(cm.commandPrefix)) {
			event.cancel();
			cm.executeCommand(b->text);
			return;
		}
	}
	return;
}

