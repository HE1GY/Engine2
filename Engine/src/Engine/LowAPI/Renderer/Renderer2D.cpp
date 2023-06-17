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
        data.shader = data.factory->CreateShader("assets\\quad_shader.glsl");
        data.vao    = data.factory->CreateVertexArray();
        data.vao->Bind();

        float vertex[] = {-0.5, -0.5, 0, 0.5, -0.5, 0, 0, 0.5, 0};

        Ref<VertexBuffer> vb = data.factory->CreateVertexBuffer(sizeof(vertex));
        vb->Bind();
        vb->SetData(vertex, sizeof(vertex));

        uint32_t index[]    = {0, 1, 2};
        Ref<IndexBuffer> ib = data.factory->CreateIndexBuffer(index, 3);
        ib->Bind();

        data.vao->SetVertexBuffer(vb, {GraphicDataType::Float3});
        data.vao->SetIndexCount(ib->GetCount());
        data.vao->UnBind();
    }

    void Renderer2D::ShutDown() {
    }

    void Renderer2D::DrawQuad() {
        data.shader->Bind();
        data.vao->Bind();
        RendererCommand::DrawIndex(data.vao);
    }
} // namespace Engine
