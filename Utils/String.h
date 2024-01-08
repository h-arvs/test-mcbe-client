#pragma once
#include <string>
#include <algorithm>

class stringutil {
public:
	static std::string lower(std::string string) {
		auto str = std::move(string);
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);
		return str;
	};
};