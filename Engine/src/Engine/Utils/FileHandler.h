#pragma once
#include <string>

namespace Engine {
    namespace Utils {
        std::string ReadFile(const std::string& path);
        void WriteFile(const std::string& path, const std::string& content);
    } // namespace Utils
} // namespace Engine
