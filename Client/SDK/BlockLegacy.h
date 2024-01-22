#pragma once
#include <string>

class BlockLegacy {
public:
	char pad_0008[32];
	std::string tileName;

	virtual ~BlockLegacy() = default;
};