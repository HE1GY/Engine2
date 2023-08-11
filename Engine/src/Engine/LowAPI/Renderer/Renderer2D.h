#pragma once


#include "Texture.h"
#include <string_view>

#include "glm/fwd.hpp"
#include "glm/vec4.hpp"

namespace Engine {

    struct Renderer2DData;

    class Renderer2D {
    public:
        enum class API { None, OpenGL };

        static void Init(API api);

        static void ShutDown();

        // static void* BeginScene(const glm::mat4& projection, const glm::mat4& view);

        // static void EndScene();

        // static void* FlushQuad();

        // static void FlushCircle();

        // static void FlushLine();

        static void DrawQuad(const glm::mat4& transform, const glm::vec4& color, const Ref<Texture>& texture);


        static Ref<Texture> CreateTexture(const std::string& path, const Texture::Properties& porp = {});

        static void OnAspectRationChange(float aspect_ration);

        // static Statistics GetStats();

        // static void ResetStats();


    private:
        static Renderer2DData data;
    };
} // namespace Engine
