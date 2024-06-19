#pragma once

// levi lamina baby

namespace mce {

    class UUID {
    public:
        uint64 a, b;
    };

};

namespace std {
template <>
struct hash<mce::UUID> {
    size_t operator()(mce::UUID const& id) const noexcept { return id.a ^ (522133279 * id.b); }
};
}