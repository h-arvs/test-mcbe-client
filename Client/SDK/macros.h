#pragma once
#include <Windows.h>
#include <assert.h>

// straight from nuvola, luv u asmmmmmmmmmmmm @:)))))))
template<int index, typename RetT, typename... ArgsT>
RetT vftCall(const void* selfPtr, ArgsT... args)
{
	const void** vftable = *((const void***)selfPtr);
	assert(vftable != nullptr);
	const void* vftfunc = vftable[index];
	assert(vftfunc != nullptr);

	return ((RetT(__thiscall*)(const void*, ArgsT...))vftfunc)(selfPtr, args...);
}

#define DIRECT_ACCESS(type, name, offset) \
type& get##name##() const { \
	return *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(this) + offset); \
}\
