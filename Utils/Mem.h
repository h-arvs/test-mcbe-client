#pragma once
#include <Windows.h>
#include <libhat\Scanner.hpp>
#include <cassert>

class Mem {
public:
	static uintptr_t FindSig(std::string_view pattern);
	template <class T> 
	static uintptr_t EvalRefSig(std::string_view pattern, int offset) 
	{
		auto address = Mem::FindSig(pattern);
		auto pointer = address + offset;
		auto casted = *reinterpret_cast<T*>(pointer);
		return (uintptr_t)reinterpret_cast<void*>(pointer + casted + sizeof(casted));
	};
};