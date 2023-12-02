#pragma once
#include <Windows.h>
#include <libhat\Scanner.hpp>
#include <cassert>

struct Mem {
	static uintptr_t FindSig(std::string_view pattern);
};