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

	static std::string replace(std::string string, std::string first, std::string second) {
		auto str = std::move(string);
		size_t pos = str.find(first);

		while (pos != std::string::npos) {
			str.replace(pos, first.length(), second);
			pos = str.find(first, pos + second.length());
		}
	};
};