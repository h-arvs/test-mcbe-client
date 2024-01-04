#include "PacketSendHook.h"
#include "../../Command/CommandManager.h"
#include "../../System.h"
#include "../../Event/Impl/PacketSendEvent.h"
#include "../../Event/EventHandler.h"

void(__fastcall* PacketSendO)(void*, Packet*);
void __fastcall PacketSend_Callback(void* _this, Packet* packet) {
	PacketSendEvent p(packet);
	EventHandler<PacketSendEvent>::trigger(p);
	if (p.isCancelled()) {
		return;
	}
	return PacketSendO(_this, packet);
}

void PacketSendHook::patch() {
	this->autoPatch("48 83 EC 28 48 0F BE 41 ? 48 83 C0 01 74 27 48 83 F8 01", &PacketSend_Callback, &PacketSendO);
}

