#pragma once
#include "../../Utils/Manager.h"
#include "Module.h"  
#include <algorithm>

class Catagory : Manager<Module> {
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
		for (auto& mod : this->modules) {
			auto modid = mod.first;
			if (modid == id) {
				return mod.second;
			}
		}
		return nullptr;
	}

	bool ichar_equals(char a, char b)
	{
		
	}

	Module* get(std::string name) {
		for (auto& mod : this->items) {
			auto modname = mod->name;
			auto n = name;
			std::transform(modname.begin(), modname.end(), modname.begin(), ::tolower);
			std::transform(n.begin(), n.end(), n.begin(), ::tolower);
			if (n.compare(modname) == 0) {
				return mod.get();
			}
		}
		return nullptr;
	}
};