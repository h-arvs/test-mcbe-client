#pragma once
#include "Math.h"
#include "WeakEntityRef.h"
// Levi lamina

enum class FacingID : char {
    Unknown = -1,
    Down = 0,
    Up = 1,
    North = 2,
    South = 3,
    West = 4,
    East = 5,
};

enum class HitResultType : int {
    Tile = 0x0,
    Entity = 0x1,
    EntityOutOfRange = 0x2,
    NoHit = 0x3,
};

struct HitResult {
    Vec3<float>         mStartPos;     // this+0x0
    Vec3<float>         mRayDir;       // this+0xC
    HitResultType       mType;         // this+0x18
    FacingID            mFacing;       // this+0x1C
    BlockPos            mBlockPos;     // this+0x20
    Vec3<float>         mPos;          // this+0x2C
    WeakEntityRef       mEntity;       // this+0x38
    bool                mIsHitLiquid;  // this+0x50
    FacingID            mLiquidFacing; // this+0x51
    BlockPos            mLiquid;       // this+0x54
    Vec3<float>         mLiquidPos;    // this+0x60
    bool                mIndirectHit;  // this+0x6C
};