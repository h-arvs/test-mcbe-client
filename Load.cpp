#include <Windows.h>
#include "Client/System.h"
#include "Client/Event/Impl/TestEvent.h"

void init() {
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
	System* system = new System();
	system->getHookManager().applyAll();
	for (auto& mod : system->getModuleManager().items) {
		mod->setState(true);
	}
	EventHandler::dispatcher.trigger<TestEvent>();
	EventHandler::dispatcher.trigger<TestEvent>();
}

bool WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, LPVOID lpRes) {

	switch (fdwReason) {

	case DLL_PROCESS_ATTACH:
		
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)init, hInstance, 0, 0);
		break;

	};

	return TRUE;

};

static_assert(sizeof(std::string) == 0x20);
