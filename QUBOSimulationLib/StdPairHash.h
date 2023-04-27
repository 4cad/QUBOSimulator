#pragma once
#include <tuple>
#include <functional>

namespace std {
    template<>
    struct hash<std::pair<short, short>> {
        std::size_t operator()(std::pair<short, short> const& p) const {
            return std::hash<int>{}((((int)p.first) << 16) + (int)p.second);
        }
    };
}