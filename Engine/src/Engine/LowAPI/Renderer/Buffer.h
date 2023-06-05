#pragma once

#include "Engine/Core/Ptrs.h"
#include <vector>
#include <string>

namespace Engine
{

	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Int, Int2, Int3, Int4, Mat3, Mat4, Bool,
	};

	uint32_t ShaderDataTypeSize(ShaderDataType type);

	struct BufferElement
	{
		std::string name;
		ShaderDataType type;
		bool normalized;
		uint32_t offset;
		uint32_t size;

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false);

		uint32_t GetComponentCount() const;

		bool operator==(const BufferElement& other)
		{
			return type == other.type && name == other.name;
		}

	};

	class BufferLayout
	{
	public:
		BufferLayout() = default;

		BufferLayout(std::initializer_list<BufferElement> layout);

		std::vector<BufferElement>::iterator begin()
		{
			return m_elements.begin();
		};

		std::vector<BufferElement>::iterator end()
		{
			return m_elements.end();
		};

		inline uint32_t GetStride()
		{
			return m_stride;
		}

		inline std::vector<BufferElement>& GetElements()
		{
			return m_elements;
		}

	private:
		void CalculateOffsetAndStride();

		std::vector<BufferElement> m_elements;
		uint32_t m_stride{ 0 };
	};

	class VertexBuffer
	{

	public:
		virtual ~VertexBuffer()
		{
		};

		static Ref<VertexBuffer> Create(uint32_t size);

		static Ref<VertexBuffer> Create(void* data, uint32_t size);

		virtual void Bind() = 0;

		virtual void UnBind() = 0;

		virtual void SetData(void* data, uint32_t size) = 0;

		virtual void SetLayout(BufferLayout layout) = 0;

		virtual BufferLayout& GetLayout() = 0;

	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer()
		{
		};

		static Ref<IndexBuffer> Create(uint32_t* data, uint32_t count);

		virtual void Bind() = 0;

		virtual void UnBind() = 0;

		virtual inline uint32_t GetCount() = 0;
	};

	/*class UniformBuffer
	{
	public:
		static Ref<UniformBuffer> Create(BufferLayout layout, uint32_t binding_point);

		virtual ~UniformBuffer()
		{
		};

		virtual void Bind() = 0;

		virtual void UnBind() = 0;

		virtual void Set(BufferElement element, const void* value) = 0;

	};*/

}; // namespace Engine