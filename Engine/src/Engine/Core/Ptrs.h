#pragma once

#include <memory>

/**
 * Own pointer count sys
 */

namespace Engine {
    template <typename T>
    using Ref = std::shared_ptr<T>;

    template <typename T>
    using Scope = std::unique_ptr<T>;

    template <typename T, typename... Args>
    Ref<T> CreateRef(Args... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    template <typename T, typename... Args>
    Scope<T> CreateScope(Args... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
} // namespace Engine
