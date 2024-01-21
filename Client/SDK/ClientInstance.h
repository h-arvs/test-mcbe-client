#pragma once
#include "macros.h"
#include "GuiData.h"

class ClientInstance {
public:
	DIRECT_ACCESS(GuiData*, GuiData, 0x560);

	void dropCursor() const
	{
		return vftCall<326, void, const ClientInstance*>(this);
	}

	void acquireCursor() const
	{
		return vftCall<327, void, const ClientInstance*>(this);
	}
};