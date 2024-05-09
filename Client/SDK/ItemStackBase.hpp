#pragma once
#include "Item.hpp"
#include "WeakPtr.h"
#include <libhat/Access.hpp>

class ItemStackBase {
public:
	WeakPtr<Item> getItem() {
		return hat::member_at<WeakPtr<Item>>(this, 0x8);
	}
};