#pragma once
namespace Neato {
	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:		return 4;
			case ShaderDataType::Float2:	return 4 * 2;
			case ShaderDataType::Float3:	return 4 * 3;
			case ShaderDataType::Float4:	return 4 * 4;
			case ShaderDataType::Mat3:		return 4 * 3 * 3;
			case ShaderDataType::Mat4:		return 4 * 4 * 4;
			case ShaderDataType::Int:		return 4;
			case ShaderDataType::Int2:		return 4 * 2;
			case ShaderDataType::Int3:		return 4 * 3;
			case ShaderDataType::Int4:		return 4 * 4;
			case ShaderDataType::Bool:		return 1;
		}
		NEATO_CORE_ASSERT(false, "Unknown Shader Data Type");
		return 0;
	}

	struct BufferElement {
		std::string Name;
		ShaderDataType Type;
		uint32_t Offset;
		uint32_t Size;
		uint32_t Count;

		BufferElement(ShaderDataType type, const std::string& name)
			: Name(name), Size(ShaderDataTypeSize(type)), Offset(0) {

		}
	};

	class BufferLayout {
	public:
		inline const std::vector<BufferElement> GetElements() const { return m_Elements; }
	private:
		std::vector<BufferElement> m_Elements;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static VertexBuffer* Create(float * vertices, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t * indices, uint32_t count);
	};
}