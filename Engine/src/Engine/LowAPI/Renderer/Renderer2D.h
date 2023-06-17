#pragma once


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

        static void DrawQuad(const glm::vec4& color);


        // static Statistics GetStats();

        // static void ResetStats();


    private:
        static Renderer2DData data;
    };
} // namespace Engine
