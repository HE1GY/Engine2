#pragma once

#include "Engine/Core/Ptrs.h"
#include <string>
#include <unordered_map>

#include "glm/glm.hpp"

namespace Engine {
    class Shader {
    public:
        virtual ~Shader()     = default;
        virtual void Bind()   = 0;
        virtual void UnBind() = 0;

        virtual void UploadUniform(const std::string& name, float value) = 0;

        virtual void UploadUniform(const std::string& name, const glm::mat4& value) = 0;

        virtual void UploadUniform(const std::string& name, const glm::vec4& value) = 0;

        virtual void UploadUniform(const std::string& name, int value) = 0;

        virtual void UploadUniform(const std::string& name, const int* value, uint32_t count) = 0;
    };
} // namespace Engine
