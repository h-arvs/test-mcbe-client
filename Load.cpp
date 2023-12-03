#include <Windows.h>
#include "Client/Command/CommandManager.h"
#include "Client/Hook/HookManager.h"
#include "Client/System.h"
#include "Utils/Mem.h"

void init() {
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
	System* sys = new System();
	System::tryGetSystem()->getHookManager().applyAll();
}

bool WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, LPVOID lpRes) {

	switch (fdwReason) {

	case DLL_PROCESS_ATTACH:
		
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)init, hInstance, 0, 0);
		break;

	};

	return TRUE;

};