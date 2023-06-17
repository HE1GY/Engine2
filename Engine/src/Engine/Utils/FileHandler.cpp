#include "FileHandler.h"

#include "Engine/Log/Log.h"
#include <fstream>
#include <sstream>

namespace Engine {
    namespace Utils {
        std::string ReadFile(const std::string& path) {
            std::ifstream in;
            in.exceptions(std::ifstream::failbit | std::ifstream::badbit);

            std::stringstream content;
            try {
                in.open(path);
                content << in.rdbuf();
                in.close();
            } catch (const std::ifstream::failure& e) {
                CORE_ERROR_LOG("Failed to open file: {0}\n Error: {1}", path, e.what());
            }

            return content.str();
        }

        void WriteFile(const std::string& path, const std::string& content) {
            std::ofstream out;
            out.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            try {
                out.open(path);
                out << content;
                out.close();
            } catch (const std::ofstream::failure& e) {
                CORE_ERROR_LOG("Failed to write to file: {0}\n Error: {1}", path, e.what());
            }
        }
    } // namespace Utils
} // namespace Engine
