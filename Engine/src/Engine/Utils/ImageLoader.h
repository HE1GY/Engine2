#pragma once

#include "Engine/Core/Ptrs.h"
#include <cstdint>
#include <stb_image.h>
#include <string>

namespace Engine {
    namespace Utils {
        struct ImageProperties {
            ImageProperties(uint8_t* data, int32_t width, int32_t height, int32_t channels)
                : data{data}, width{width}, height{height}, channels{channels} {
            }
            ~ImageProperties() {
                stbi_image_free(data);
            }
            uint8_t* data;
            int32_t width, height, channels;
        };

        void LoadImage(const std::string& path, Ref<ImageProperties>& out_img_prop);
    } // namespace Utils
} // namespace Engine
