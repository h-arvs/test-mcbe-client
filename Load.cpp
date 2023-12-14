#include <Windows.h>
#include "Client/System.h"

void init() {
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
	System* system = new System();
	system->getHookManager().applyAll();
	for (auto& i : system->getModuleManager().items) {
		printf(i->name.c_str());
	}
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
