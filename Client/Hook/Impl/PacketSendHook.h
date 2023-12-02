#pragma once
#include "Hook.h"

class PacketSendHook : public Hook {
	void patch() override;
};