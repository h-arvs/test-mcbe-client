#pragma once

#include "Module.h"

class TestModule : public Module {
	std::string_view getName() override;
};