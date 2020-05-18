#include "NeatoPCH.h"
#include "Application.h"
#include "Neato/Log.h"
#include "Neato/Renderer/Renderer.h"

namespace Neato {
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)
    
	Application* Application::s_Instance = nullptr;

	Application::Application() :
		m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
    {
		NEATO_CORE_ASSERT(!s_Instance, "Multiple application instances");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		m_VertexArray.reset(VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.1f, 0.4f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.6f, 0.2f, 1.0f,
			 0.0f,  0.5f, 0.0f,	0.7f, 0.2f, 0.5f, 1.0f
		};

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		
		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"}
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = {
			0,1,2
		};

		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location=0) in vec3 a_Position;
			layout(location=1) in vec4 a_Color;

			uniform mat4 u_ProjectionView;

			out vec3 v_Position;
			out vec4 v_Color;

			void main() {
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ProjectionView * vec4(a_Position, 1.0);
			}
		)";

		std::string fragSrc = R"(
			#version 330 core
			in vec3 v_Position;
			in vec4 v_Color;
			layout(location = 0) out vec4 color;
			void main() {
				color = vec4(v_Color.xyz * v_Position, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragSrc));
		m_Shader->Bind();

		m_SquareVA.reset(VertexArray::Create());

		float squareVert[3 * 4] = {
			 -0.75f, -0.75f, 0.0f,
			  0.75f, -0.75f, 0.0f,
			  0.75f,  0.75f, 0.0f,
			 -0.75f,  0.75f, 0.0f,
		};

		std::shared_ptr<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squareVert, sizeof(squareVert)));

		BufferLayout layoutBlue = {
			{ShaderDataType::Float3, "a_Position"}
		};

		squareVB->SetLayout(layoutBlue);
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareInd[2 * 3] = {
			0,1,2,2,3,0
		};

		std::shared_ptr<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareInd, sizeof(squareInd) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string blueVertexSrc = R"(
			#version 330 core

			layout(location=0) in vec3 a_Position;
			uniform mat4 u_ProjectionView;

			void main() {
				gl_Position = u_ProjectionView * vec4(a_Position, 1.0);
			}
		)";

		std::string blueFragSrc = R"(
			#version 330 core
			layout(location = 0) out vec4 color;
			void main() {
				color = vec4(0.2, 0.3, 0.85, 1.0);
			}
		)";

		m_BlueShader.reset(new Shader(blueVertexSrc, blueFragSrc));
		m_BlueShader->Bind();
	}

    Application::~Application()
    {
    }

    void Application::Run() {
        
		while (m_Running)
		{
			RenderCommand::SetClearColor({0.1f, 0.2f, 0.1f, 1});
			RenderCommand::Clear();

			m_Camera.SetPosition({0.5f, 0.5f, 0.5f});
			m_Camera.SetRotation(45.0f);

			Renderer::BeginScene(m_Camera);
			Renderer::Submit(m_BlueShader, m_SquareVA);
			Renderer::Submit(m_Shader, m_VertexArray);
			Renderer::EndScene();

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
    }

	void Application::OnEvent(Event & e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) 
		{
			(*--it)->OnEvent(e);
			if (e.Handled) break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}

