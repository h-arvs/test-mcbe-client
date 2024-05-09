#pragma once

#include <libhat/Access.hpp>
#include "TexturePtr.h"

class ItemRenderer {
public:
	mce::TexturePtr& getTexture() {
		return hat::member_at<mce::TexturePtr>(this, 0xd0);
	}
};