#pragma once
#include "Packet.h"

class TextPacket : Packet
{
public:
	char pad_0030[8]; //0x0030
	std::string username; //0x0038
	std::string text; //0x0058
	char pad_0078[24]; //0x0078
	bool requireTranslation; //0x0090
	char pad_0091[7]; //0x0091
	std::string xuid; //0x0098
	std::string platformChatId; //0x00B8
	char pad_00D8[1096]; //0x00D8
}; 

