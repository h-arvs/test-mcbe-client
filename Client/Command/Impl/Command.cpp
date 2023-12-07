#include "Command.h"
#include "../../System.h"

void Command::reply(std::string& msg) {
	System::tryGetSystem()->getCommandManager().reply(msg);
}

executeResult Command::caughtExecute(std::vector<std::string> args) {
	try {
		this->execute(args);
		return executeResult::COMMANDEXECUTED;
	}
	catch (...) {
		return executeResult::COMMANDFAILED;
	}
}