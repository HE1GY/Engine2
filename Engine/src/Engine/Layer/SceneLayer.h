#pragma once


#include "Engine/Core/Layer.h"
#include "Engine/LowAPI/Renderer/Shader.h"
#include "Engine/LowAPI/Renderer/VertexArray.h"

namespace Engine {
    class SceneLayer : public Layer {
    public:
        SceneLayer(const std::string& name) : Layer{name} {
        }

        virtual ~SceneLayer() override = default;

        virtual void OnAttach(WindowEvents& events) override;

        virtual void OnDetach(WindowEvents& events) override;

        virtual void OnUpdate() override;

    private:
        Ref<VertexArray> m_vao;
        Ref<Shader> m_shader;

        glm::vec4 m_color{1, 1, 1, 1};
        bool m_rising{true};
    };
} // namespace Engine
