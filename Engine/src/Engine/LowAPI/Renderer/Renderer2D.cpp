#include "Renderer2D.h"

#include "Engine/Log/Log.h"
#include "GraphicObjectFactory.h"
#include "Platform/OpenGL/OpenGLObjectFactory.h"
#include "RendererCommand.h"
#include "Shader.h"
#include "VertexArray.h"


namespace Engine {
    struct Renderer2DData {
        Scope<GraphicObjectFactory> factory;
        Ref<Shader> shader;
        Ref<VertexArray> vao;
        Ref<Texture> texture;
        Ref<Texture> texture2;
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
        data.shader->UploadUniform("u_texture2", 1);


        Texture::Properties pr;
        pr.use_mipmaps = false;
        pr.wrapS       = Texture::Wrapping::Repeat;
        pr.wrapT       = Texture::Wrapping::Repeat;
        pr.min         = Texture::Filtering::Nearest;
        pr.mag         = Texture::Filtering::Nearest;

        data.texture = data.factory->CreateTexture(pr, "Game/assets/pexels-pixabay-268533.jpg");
        data.texture->Bind(0);
        data.texture2 = data.factory->CreateTexture(pr, "Game/assets/awesomeface.png");
        data.texture2->Bind(1);

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

    void Renderer2D::DrawQuad(const glm::vec4& color) {
        data.shader->Bind();
        data.vao->Bind();
        RendererCommand::DrawIndex(data.vao);
    }
} // namespace Engine
