#pragma omce
#include <string>

class TestEvent {
public:
	std::string val = "Test Event!";
	void setVal(std::string v) {
		this->val = v;
	}
};