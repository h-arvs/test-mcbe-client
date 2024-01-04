#pragma once
#include "../../SDK/Packet.h"

class PacketSendEvent {
	Packet* packet;
	bool cancelled = false;
public:

	PacketSendEvent(Packet* p) : packet(p) {};

	Packet* getPacket() {
		return this->packet;
	}

	bool isCancelled() {
		return this->cancelled;
	}

	void cancel() {
		this->cancelled = true;
	}
};