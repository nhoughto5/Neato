#include "NeatoPCH.h"
#include "Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Neato/Renderer/Renderer.h"

namespace Neato {
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			NEATO_CORE_ASSERT(false, "RendererAPI::None not supported");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(vertexSrc, fragmentSrc);
		}
		return nullptr;
	}
}

