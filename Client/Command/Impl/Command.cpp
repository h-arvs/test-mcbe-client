#include "Command.h"
#include "../../System.h"

void Command::reply(std::string& msg) {
	System::tryGetSystem()->getCommandManager().reply(msg);
}
