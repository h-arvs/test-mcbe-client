#include <Windows.h>
#include "client/CommandManager.h"
#include "Utils/Mem.h"

void init() {
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
	//CommandManager* cm = new CommandManager();
	//cm->executeCommand("!ping arg1 arg2");
	auto a = Mem::EvalRefSig<uint32_t>("48 8D 05 ? ? ? ? 48 89 06 33 C0 48 89 86 ? ? ? ? 48 89 86 ? ? ? ? 48 89 86", 3);
	printf("%p\n", a); // Player vtable ref
}

bool WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, LPVOID lpRes) {

	switch (fdwReason) {

	case DLL_PROCESS_ATTACH:

		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)init, hInstance, 0, 0);
		break;

	};

	return TRUE;

};