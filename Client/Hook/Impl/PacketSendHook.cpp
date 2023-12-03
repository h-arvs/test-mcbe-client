#include "PacketSendHook.h"
#include "../../Command/CommandManager.h"
#include "../../System.h"
void(__fastcall* PacketSendO)(void*, Packet*);
void __fastcall PacketSend_Callback(void* _this, Packet* packet) {
	auto a = packet->getId();
	if (a == PacketID::TextPacket) {
		auto b = reinterpret_cast<TextPacket*>(packet);
		auto& cm = System::tryGetSystem()->getCommandManager();
		if (b->text.starts_with(cm.commandPrefix)) {
			cm.executeCommand(b->text);
			return;
		}
	}
	return PacketSendO(_this, packet);
}

void PacketSendHook::patch() {
	this->autoPatch("48 83 EC 28 48 0F BE 41 ? 48 83 C0 01 74 27 48 83 F8 01", &PacketSend_Callback, &PacketSendO);
}

