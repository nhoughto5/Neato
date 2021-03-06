#pragma once
#include "Neato/Renderer/RendererAPI.h"

namespace Neato {
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;
		virtual void SetClearColor(const glm::vec4 color);
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
		virtual void Clear();
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray);

	private:
	};
}