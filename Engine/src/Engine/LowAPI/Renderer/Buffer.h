#pragma once

#include "Engine/Core/Ptrs.h"
#include <string>
#include <vector>

namespace Engine {
    enum class GraphicDataType {
        Float2,
        Float3,
    };

    class VertexBuffer {
    public:
        virtual ~VertexBuffer()                       = default;
        virtual void Bind()                           = 0;
        virtual void UnBind()                         = 0;
        virtual void SetData(void* data, size_t size) = 0;
    };

    class IndexBuffer {
    public:
        virtual ~IndexBuffer()      = default;
        virtual void Bind()         = 0;
        virtual void UnBind()       = 0;
        virtual uint32_t GetCount() = 0;
    };


    /*struct BufferElement {
        std::string name;
        ShaderDataType type;
        bool normalized;

 *





     * * * * * * uint32_t


     * * * offset;
        uint32_t size;

        BufferElement(ShaderDataType type,
     * const


     * * *


     * * * std::string& name, bool
 *

     * * normalized = false);

        uint32_t
     * GetComponentCount()

     * * const;


     * bool


     * * * operator==(const
     * BufferElement&

     * *
     * other) { return type ==

     * * other.type && name ==
     * other.name;
     * }


     * * };

    class

     * * BufferLayout {
 public:




     * * * * BufferLayout() =
     * default;


     *
 *

     * *
     * BufferLayout(std::initializer_list<BufferElement>

     * * layout);


     *
     *
     *
     *
     * std::vector<BufferElement>::iterator


     * * * begin() { return

     * * m_elements.begin(); }


     *
 *

     * *
     * std::vector<BufferElement>::iterator end() { return


 *

     * * * * m_elements.end(); }

 inline
     * uint32_t

     * * GetStride() {

     * * return m_stride; }


     * inline

     * *

     * *
     * std::vector<BufferElement>&
     * GetElements()
     * { return m_elements; }



     * * private:


     * *
     * void
     *
     *
     *
     * CalculateOffsetAndStride();


     *
     * std::vector<BufferElement>
     * m_elements;

     * uint32_t
     * m_stride{0};

 *



     * * * * };

    class
     * VertexBuffer
     * {


     * public:
        virtual
     * ~VertexBuffer(){};

        static
     *

     * *


     * * *
     * Ref<VertexBuffer>

     * * Create(uint32_t
     * size);

        static Ref<VertexBuffer> Create(void*

     *
     * * data,
     * uint32_t


     * * *
     * size);


     * virtual void
     * Bind() = 0;

        virtual

     * * void
     * UnBind() = 0;


     * virtual void


 * *
     * *
     * SetData(void* data, uint32_t size) =
     * 0;



     * * virtual void
     * SetLayout(BufferLayout
     * layout) =
     * 0;


     * virtual


     * *
     * *
     * BufferLayout& GetLayout() = 0;
    };


     * class
     * IndexBuffer {

     * public:

     *
     * virtual

     *
     * *
     *
     * ~IndexBuffer(){};

        static
     * Ref<IndexBuffer>
     *
     * Create(uint32_t*
     * data,

     * * uint32_t
     * count);

 virtual
     * void

     * *
     * Bind() =
     * 0;


     * virtual void UnBind() =
     * 0;

 virtual
     *
     *
     * inline uint32_t GetCount()
     *

     * * = 0;
 };*/


}; // namespace Engine
