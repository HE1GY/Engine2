#include "SceneLayer.h"

#include "Engine/LowAPI/Renderer/Buffer.h"
#include "Engine/LowAPI/Renderer/Renderer2D.h"
#include "Engine/LowAPI/Renderer/Shader.h"
#include "Engine/LowAPI/Renderer/VertexArray.h"
#include "glad/glad.h"


namespace Engine {
    void SceneLayer::OnAttach(Engine::WindowEvents& events) {
        {
            /*float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 0.0f, -0.5f,
             * 0.5f,
                0.0f, -0.5f, -0.5f, 0.0f};


            Ref<VertexBuffer> vb =
             * VertexBuffer::Create(vertices, sizeof(vertices));
            vb->Bind();

             * vb->SetLayout({{ShaderDataType::Float3, "a_position"}});


            m_vao = VertexArray::Create();

             * m_vao->Bind();
            m_vao->SetVertexBuffer(vb);

            m_shader =
             * Shader::Create("E:/dev/Engine2/Engine/assets/Shader.glsl");
            m_shader->Bind();
        }

 {

             * float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 0.0f, -0.5f,
             * 0.5f,
                0.0f, -0.5f, -0.5f, 0.0f};


            Ref<VertexBuffer> vb =
             * VertexBuffer::Create(vertices, sizeof(vertices));
            vb->Bind();

             * vb->SetLayout({{ShaderDataType::Float3, "a_position"}});


            m_vao = VertexArray::Create();

             * m_vao->Bind();
            m_vao->SetVertexBuffer(vb);

            m_shader =
             * Shader::Create("E:/dev/Engine2/Engine/assets/Shader.glsl");
            m_shader->Bind();*/
        }
    }

    void SceneLayer::OnDetach(WindowEvents& events) {}

    void SceneLayer::OnUpdate() {
        /*glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

 glDrawArrays(GL_TRIANGLES, 0,
         * 6);*/

        Renderer2D::DrawQuad();
    }

} // namespace Engine
