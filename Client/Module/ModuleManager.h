#pragma once

#include "Module.h"
#include "../../Utils/Manager.h"
#include "Catagory.h"

class ModuleManager : public Manager<Catagory> {
public:
	ModuleManager();

	template <class T>
	Module* get() {
		for (auto& c : this->items) {
			auto mod = c->get<T>();
			if (mod != nullptr) return mod;
		}
		return nullptr;
	}
};