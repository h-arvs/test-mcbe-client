#pragma once
#include <string>

enum class PacketPriority {
	High,
	Immediate,
	Low,
	Medium,
	Count
};

enum class Reliability {
	Reliable,
	ReliableOrdered,
	Unreliable,
	UnreliableSequenced
};

enum class Compressibility {
	Compressible,
	Incompressible
};

enum class PacketID : int {
	TextPacket = 9,
	MoveEntityAbsolutePacket = 0x12,
	MovePlayerPacket = 0x13,
	InteractPacket = 0x21,
	ContainerOpenPacket = 0x2e,
	ContainerClosePacket = 0x2f,
	NetworkStackLatencyPacket = 0x73,
	LevelSoundEventPacket = 0x7b,
	PlayerAuthInputPacket = 0x90,
	ItemStackRequestPacket = 0x93,
	MobEquipmentPacket = 0x1F
};

struct Packet {
	/* Fields */
	PacketPriority packetPriority = PacketPriority::Low; //0x0008
	Reliability peerReliability = Reliability::Reliable; //0x000C
	uint64_t clientSubID; //0x0010
	char pad_0018[8]; //0x0018
	void* packetHandlerDispatcher; //0x0020
	Compressibility compressType = Compressibility::Compressible; //0x0028
	char pad_002C[4]; //0x002C
	/* Virtuals */
	virtual ~Packet() {};
	virtual auto getId() -> PacketID { return (PacketID)0; };
	virtual auto getName() -> std::string { return "INVALID"; };
	/* Functions */
	Packet()
	{

	}
};