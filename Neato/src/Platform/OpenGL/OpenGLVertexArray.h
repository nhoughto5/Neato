#pragma once
#include "Neato/Renderer/Buffer.h"
#include "Neato/Renderer/VertexArray.h"

namespace Neato {
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		
		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; };
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; };

		static OpenGLVertexArray* Create();
	private:
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;

		uint32_t m_RendererID;
	};
}