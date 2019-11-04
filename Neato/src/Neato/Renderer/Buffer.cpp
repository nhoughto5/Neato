#include "NeatoPCH.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Neato {
	VertexBuffer* VertexBuffer::Create(float * vertices, uint32_t size)
	{
		switch (Renderer::GetAPI()) 
		{
			case RendererAPI::API::None:
				NEATO_CORE_ASSERT(false, "RendererAPI::None not supported");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return new OpenGLVertexBuffer(vertices, size);
		}

		NEATO_CORE_ASSERT(false, "Undefined API");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t * indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			NEATO_CORE_ASSERT(false, "RendererAPI::None not supported");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLIndexBuffer(indices, count);
		}

		NEATO_CORE_ASSERT(false, "Undefined API");
		return nullptr;
	}
}