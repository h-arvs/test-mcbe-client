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

	Module* get(std::string name) {
		for (auto& c : this->items) {
			auto mod = c->get(name);
			if (mod != nullptr) return mod;
		}
		return nullptr;
	}

	Module* getA(std::string name) {
		return this->get(stringutil::replace(name, "_", ""));
	}
};