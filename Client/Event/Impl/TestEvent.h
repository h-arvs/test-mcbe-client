#pragma once
#include <string>

class TestEvent {
public:
	std::string val;
	TestEvent(std::string hold, std::string str) {
		this->val = str;
	}
	void setVal(std::string v) {
		this->val = v;
	}
};