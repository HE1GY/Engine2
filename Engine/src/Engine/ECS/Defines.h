#pragma once

#include <bitset>

namespace Engine {
    using ComponentID = std::uint8_t;
    constexpr ComponentID k_max_components{32};
    using Signature = std::bitset<k_max_components>;
} // namespace Engine
