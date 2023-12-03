#pragma once
#include "Hook.h"
#include "../../System.h"

class ClientInstance;
class CIUpdateHook : public Hook {
	void patch() override;
};
