#pragma once
#include "macros.h"
#include "GuiData.h"
#include "LocalPlayer.h"

class ClientInstance {
public:
	GuiData* getGuiData() {
		return hat::member_at<GuiData*>(this, 0x558);
	}

	void dropCursor() const
	{
		return vftCall<330, void>(this);
	}

	void acquireCursor() const
	{
		return vftCall<331, void>(this);
	}

	LocalPlayer* getClientPlayer() {
		return vftCall<29, LocalPlayer*>(this);
	}
};