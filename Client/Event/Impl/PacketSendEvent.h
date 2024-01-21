#pragma once
#include "../../SDK/Packet.h"
#include "Cancellable.h"

class PacketSendEvent : public Cancellable {
	Packet* packet;
public:

	PacketSendEvent(Packet* p) : packet(p) {};

	Packet* getPacket() {
		return this->packet;
	}
};