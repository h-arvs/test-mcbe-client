#pragma once
#include "../../Utils/Mem.h"
#include "ActorFlags.h"

class SynchedActorDataEntityWrapper {
public:
	bool getStatusFlag(ActorFlags flag) {
		static auto sig = Mem::FindSig("48 83 EC ? 4C 8B 81 ? ? ? ? 4D 85 C0 74 5B");
		using func = bool(__fastcall*)(SynchedActorDataEntityWrapper*, ActorFlags);
		func _func = (func)sig;
		_func(this, flag);
	}
};