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
			case RendererAPI::None:
				NEATO_CORE_ASSERT(false, "RendererAPI::None not supported");
				return nullptr;
			case RendererAPI::OpenGL:
				return new OpenGLVertexArray();
		}
		return nullptr;
	}
}

