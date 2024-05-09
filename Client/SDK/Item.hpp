#pragma once
#include <libhat/Access.hpp>
#include "HashedString.hpp"

class Item {
public:
	void setGlint(bool state) {
		hat::member_at<bool>(this, 0x14A) = state;
	}

	HashedString getName() {
		return hat::member_at<HashedString>(this, 0x118);
	}

	std::string getRawNameId() {
		return hat::member_at<std::string>(this, 0xd0);
	}
};