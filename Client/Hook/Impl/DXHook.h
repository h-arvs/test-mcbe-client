#pragma once
#include "Hook.h"

class DirectXHook : public Hook {
	void patch() override;
	void disablePatch() override;
};