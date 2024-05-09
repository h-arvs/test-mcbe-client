#pragma once
#include "Hook.h"
#include "../../SDK/MCE/Color.h"

class TestHook : public Hook {
public:
	inline static mce::Color* color;
	inline static mce::Color original;
	void patch() override;

};
