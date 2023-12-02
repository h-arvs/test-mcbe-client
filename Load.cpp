#include <Windows.h>
#include "client/CommandManager.h"
#include "Utils/Mem.h"

void init() {
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
	//CommandManager* cm = new CommandManager();
	//cm->executeCommand("!ping arg1 arg2");
	printf("%p\n", Mem::FindSig("48 89 5c 24 ? 48 89 74 24 ? 55 57 41 54 41 56 41 57 48 8d ac 24 ? ? ? ? 48 81 ec ? ? ? ? 48 8b 05 ? ? ? ? 48 33 c4 48 89 85 ? ? ? ? 44 0f b6 f2 48 8b f1")); //ClientInstance::Update
}

bool WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, LPVOID lpRes) {

	switch (fdwReason) {

	case DLL_PROCESS_ATTACH:

		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)init, hInstance, 0, 0);
		break;

	};

	return TRUE;

};