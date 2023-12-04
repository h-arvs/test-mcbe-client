#pragma once
#include <string>

class Module {
public:
	virtual std::string_view getName() = 0;
};