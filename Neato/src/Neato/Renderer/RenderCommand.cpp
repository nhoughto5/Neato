#include "NeatoPCH.h"
#include "Neato/Renderer/RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Neato {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}