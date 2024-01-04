#pragma once
#include "Command.h"
#include "../../Utils/Manager.h"
#include "../Event/Listener.h"

class PacketSendEvent;
class CommandManager : public Manager<Command>, public Listener{
public:
	std::string commandPrefix = "!";
	void executeCommand(std::string rawCommandString);
	std::unique_ptr<Command>& findCommand(std::string name);
	void reply(std::string&);
	CommandManager();
	void onPacketSend(PacketSendEvent&);
};