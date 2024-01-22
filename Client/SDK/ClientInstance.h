#pragma once
#include "macros.h"
#include "GuiData.h"
#include "LocalPlayer.h"

class ClientInstance {
public:
	DIRECT_ACCESS(GuiData*, GuiData, 0x560);

	void dropCursor() const
	{
		return vftCall<326, void>(this);
	}

	void acquireCursor() const
	{
		return vftCall<327, void>(this);
	}

	LocalPlayer* getClientPlayer() {
		return vftCall<28, LocalPlayer*>(this);
	}
};