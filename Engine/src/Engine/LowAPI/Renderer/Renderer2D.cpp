#include "Renderer2D.h"

#include "Engine/Log/Log.h"
#include "GraphicObjectFactory.h"
#include "Platform/OpenGL/OpenGLObjectFactory.h"
#include "RendererCommand.h"
#include "Shader.h"
#include "VertexArray.h"

#include "glm/ext/matrix_clip_space.hpp"


namespace Engine {
    struct Renderer2DData {
        Scope<GraphicObjectFactory> factory;
        Ref<Shader> shader;
        Ref<VertexArray> vao;
        Ref<Texture> texture;
        Ref<Texture> texture2;

        float aspect_ratio;
    };

    Renderer2DData Renderer2D::data;

    void Renderer2D::Init(Renderer2D::API api) {
        /** Api selection**/
        switch (api) {
        case API::OpenGL:
            data.factory = CreateScope<OpenGLObjectFactory>();
            break;
        case API::None:
        default:
            CORE_ERROR_LOG("None renderer API not supported!");
        }

        RendererCommand::Init();

        /** Default resources*/

        data.shader = data.factory->CreateShader("Engine\\assets\\quad_shader.glsl");
        data.shader->Bind();

        data.shader->UploadUniform("u_texture", 0);
        data.texture = data.factory->CreateTexture();
        data.texture->Bind(0);

        data.vao = data.factory->CreateVertexArray();
        data.vao->Bind();
        {
            float vertex[] = {-0.5, -0.5, 0, 0, 0, 0.5, -0.5, 0, 1, 0, 0.5, 0.5, 0, 1, 1, -0.5, 0.5, 0, 0, 1};

            Ref<VertexBuffer> vb = data.factory->CreateVertexBuffer(sizeof(vertex));
            vb->Bind();
            vb->SetData(vertex, sizeof(vertex));
            data.vao->SetVertexBuffer(vb, {GraphicDataType::Float3, GraphicDataType::Float2});

            uint32_t index[]    = {0, 1, 2, 2, 3, 0};
            Ref<IndexBuffer> ib = data.factory->CreateIndexBuffer(index, sizeof(index) / sizeof(uint32_t));
            ib->Bind();
            data.vao->SetIndexCount(ib->GetCount());

            data.vao->UnBind();
        }
    }

    void Renderer2D::ShutDown() {
    }

    void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color, const Ref<Texture>& texture) {

        data.shader->Bind();
        data.shader->UploadUniform(
            "u_projection_view", glm::ortho(-data.aspect_ratio, data.aspect_ratio, -1.0f, 1.0f, -1.0f, 1.0f));
        data.shader->UploadUniform("u_transform", transform);
        data.shader->UploadUniform("u_color", color);

        texture->Bind(0);
        data.vao->Bind();

        RendererCommand::DrawIndex(data.vao);
    }

    Ref<Texture> Renderer2D::CreateTexture(const std::string& path, const Texture::Properties& porp) {
        return data.factory->CreateTexture(porp, path);
    }

    void Renderer2D::OnAspectRationChange(float aspect_ration) {
        data.aspect_ratio = aspect_ration;
    }
} // namespace Engine
