#pragma once

#include "Engine/Core/Ptrs.h"
#include <string>

namespace Engine {


    class Texture {
    public:
        enum class Wrapping : int8_t {
            Repeat,         // The default behavior for textures. Repeats the texture image.
            MirroredRepeat, // Same as Repeat but mirrors the image with each repeat.
            ClampToEdge,    // Clamps the coordinates between 0 and 1. The result is that higher coordinates
            ClampToBorder,  // Coordinates outside the range are now given a user-specified border color.
        };
        enum class Filtering : int8_t {
            Nearest, // selects the texel that center is closest to the texture coordinate
            Linear,  // takes an interpolated value from the texture coordinate's neighboring texels, approximating a
                     // color between the texels
        };
        enum class Mipmaps : int8_t {
            NearestNearest, // takes the nearest mipmap to match the pixel size and uses nearest neighbor interpolation
                            // for texture sampling.
            LinearLinear,   // takes the nearest mipmap level and samples that level using linear interpolation.
            LinearNearest,  // linearly interpolates between the two mipmaps that most closely match the size of a pixel
                            // and samples the interpolated level via nearest neighbor interpolation.
            NearestLinear,  // linearly interpolates between the two closest mipmaps and samples the interpolated level
                            // via linear interpolation.
        };

        struct Properties {
            Wrapping wrapS{Wrapping::Repeat};
            Wrapping wrapT{Wrapping::Repeat};
            Filtering mag{Filtering::Linear};
            Filtering min{Filtering::Linear};
            Mipmaps mipmaps{Mipmaps::NearestNearest};

            bool use_mipmaps{true};
        };

        virtual ~Texture() = default;

        virtual uint32_t GetWidth() const = 0;

        virtual uint32_t GetHeight() const = 0;

        virtual uint32_t GetRendererId() = 0;

        virtual void Bind(uint32_t slot = 0) = 0;
    };
} // namespace Engine
