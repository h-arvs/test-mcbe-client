#include "Mem.h"

uintptr_t Mem::FindSig(std::string_view pattern) {
    auto sig = hat::parse_signature(pattern);
    assert(sig.has_value());
    auto result = hat::find_pattern(sig.value(), ".text");
    return result.has_result() ? reinterpret_cast<uintptr_t>(result.get()) : NULL;
}