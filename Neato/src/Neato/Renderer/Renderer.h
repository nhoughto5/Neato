#pragma once
#include "RenderCommand.h"
#include "RendererAPI.h"
#include "OrthographicCamera.h"
#include "Shader.h"

namespace Neato
{
	class Renderer
	{
	public:
		static void Init();
		static void OnWindowResize(uint32_t width, uint32_t size);
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();
		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ProjectionViewMatrix;
		};

		static SceneData* m_SceneData;
	};
}

