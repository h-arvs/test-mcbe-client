#pragma once
#include <memory>

template <typename T>
struct WeakRef {
	std::weak_ptr<T> mHandle;
};