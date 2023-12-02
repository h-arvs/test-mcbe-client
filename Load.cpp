#include <Windows.h>
#include "client/CommandManager.h"

void init() {
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
	CommandManager* cm = new CommandManager();
	cm->executeCommand("!ping arg1 arg2");
}

bool WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, LPVOID lpRes) {

	switch (fdwReason) {

	case DLL_PROCESS_ATTACH:

		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)init, hInstance, 0, 0);
		break;

	};

	return TRUE;

};