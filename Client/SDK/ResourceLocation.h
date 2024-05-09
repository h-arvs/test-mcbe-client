#pragma once

#include "ResourceFileSystem.h"
#include "PathBuffer.h"
#include "ResourceFileSystem.h"

namespace Core { class Path; }
namespace Json { class Value; }

class ResourceLocation {
public:
    ResourceFileSystem            mFileSystem; // this+0x0
    Core::PathBuffer<std::string> mPath;       // this+0x8
    uint64_t                        mPathHash;   // this+0x28
    uint64_t                        mFullHash;   // this+0x30
};
