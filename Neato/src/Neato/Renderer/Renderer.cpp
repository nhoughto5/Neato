#include "NeatoPCH.h"
#include "Renderer.h"

namespace Neato {
	RendererAPI Renderer::s_Renderer = RendererAPI::OpenGL;
	Renderer::Renderer()
	{
	}

	Renderer::~Renderer()
	{
	}
}