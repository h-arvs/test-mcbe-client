#pragma once

struct MoveInputComponent {
	char pad_0000[2];
	bool mWantDownSlow;
	char pad_0004[124];
    bool mWantDown; 
	char pad_0080[8];
}; // size: 0x88 ( 136 )

static_assert(sizeof(MoveInputComponent) == 0x88);