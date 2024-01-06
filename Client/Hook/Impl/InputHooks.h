#pragma once
#include "Hook.h"


class MouseInputHook : public Hook {
	void patch() override;
};

class KeyBoardInputHook : public Hook {
	void patch() override;
};
