#pragma once
#include <vector>
#include <memory>

template<class T> class Manager {
public:
	std::vector<std::unique_ptr<T>> items;
	template<class U> U* addItem() {
		auto a = std::make_unique<U>();
		auto* b = a.get();
		this->items.push_back(std::move(a));
		return b;
	};
	template<class... Us> bool addItems() {
		(this->addItem<Us>(), ...);
		return true;
	};
};