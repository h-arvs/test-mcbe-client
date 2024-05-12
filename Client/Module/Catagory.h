#pragma once
#include "../../Utils/Manager.h"
#include "../../Utils/StringUtil.h"
#include "Module.h"

class Catagory : public Manager<Module> {
	std::string name;
	std::unordered_map<entt::id_type, Module*> modules;
public:
	Catagory(std::string name) : name(std::move(name)) {};
	std::string getName() {
		return this->name;
	}

	template <class U>
	bool addModule() {
		auto* mod = this->addItem<U>();
		this->modules.insert({ entt::type_hash<U>(), mod });
		return true;
	}

	template<class... Us> bool addModules() {
		(this->addModule<Us>(), ...);
		return true;
	};

	template <class T> Module* get() {
		auto id = entt::type_hash<T>();
		auto lookup = this->modules.find(id);
		if (lookup != this->modules.end()) return lookup->second;
		return nullptr;
	}

	Module* get(std::string name) {
		for (auto& mod : this->items) {
			auto modname = mod->name;
			auto n = name;
			if (stringutil::lower(n).compare(stringutil::lower(modname)) == 0) {
				return mod.get();
			}
		}
		return nullptr;
	}

	Module* getA(std::string n) {
		return this->get(stringutil::replace(n, "_", " "));
	}
};
