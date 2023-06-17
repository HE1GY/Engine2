#include "ImageLoader.h"

#include "Engine/Log/Log.h"


namespace Engine {
    namespace Utils {
        void LoadImage(const std::string& path, Ref<ImageProperties>& out_img_prop) {
            stbi_set_flip_vertically_on_load(true);
            int32_t width, height, channels;
            stbi_uc* data = nullptr;
            data          = stbi_load(path.c_str(), &width, &height, &channels, 0);
            if (!data) {
                CORE_ERROR_LOG("Failed to load image!");
                const char* reason = stbi_failure_reason();
                CORE_ERROR_LOG(reason);
                CORE_ASSERT_LOG(false, "Path: {0}", path);
            }
            out_img_prop = CreateRef<ImageProperties>(data, width, height, channels);
        }
    } // namespace Utils
} // namespace Engine
