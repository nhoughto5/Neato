#include "NeatoPCH.h"
#include "Texture.h"
#include "Neato/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Neato
{

	Ref<Neato::Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			NEATO_CORE_ASSERT(false, "RendererAPI::None not supported");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(path);
		}
		return nullptr;
	}

}

