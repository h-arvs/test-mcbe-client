#pragma once
#include <Windows.h>

#define DIRECT_ACCESS(type, name, offset) \
type& get##name() const { \
	return *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(this) + offset); \
}\
