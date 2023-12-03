#pragma once

#include "../../Utils/Mem.h"

class GuiData {
public:
	void displayMessage(std::string& msg) {
		static auto sig = Mem::FindSig("40 55 53 56 57 41 56 48 8d 6c 24 ? 48 81 ec ? ? ? ? 48 8b 05 ? ? ? ? 48 33 c4 48 89 45 ? 41 0f b6 f0");
		using func = void(__fastcall*)(GuiData*, std::string);
		func _func = (func)sig;
		_func(this, msg);
	}
};