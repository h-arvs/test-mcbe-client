#include "PacketSendHook.h"


void(__fastcall* PacketSendO)(void*, void*);
void __fastcall PacketSend_Callback(void* _this, void* packet) {
	printf("packet");
	return PacketSendO(_this, packet);
}

void PacketSendHook::patch() {
	this->AutoPatch("48 83 EC 28 48 0F BE 41 ? 48 83 C0 01 74 27 48 83 F8 01", &PacketSend_Callback, &PacketSendO);
}