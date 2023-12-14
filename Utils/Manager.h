#pragma once
#include <vector>
#include <memory>

template<class T> class Manager {
public:
	std::vector<std::unique_ptr<T>> items;
	template<class U> bool addItem() {
		this->items.push_back(std::make_unique<U>());
		return true;
	};
	template<class... Us> bool addItems() {
		(this->addItem<Us>(), ...);
		return true;
	};
};