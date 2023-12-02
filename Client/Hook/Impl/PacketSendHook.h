#pragma once
#include "Hook.h"
#include "../../SDK/TextPacket.h"

class PacketSendHook : public Hook {
	void patch() override;
};

static_assert(sizeof(std::string) == 32);