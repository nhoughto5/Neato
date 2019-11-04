#include "NeatoPCH.h"
#include "VertexArray.h"
#include "Neato/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
namespace Neato {

	VertexArray::~VertexArray()
	{
	}

	VertexArray * VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				NEATO_CORE_ASSERT(false, "RendererAPI::None not supported");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return new OpenGLVertexArray();
		}
		return nullptr;
	}
}

