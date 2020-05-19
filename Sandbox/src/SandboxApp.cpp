#include <Neato.h>
#include <stdio.h>
#include "imgui/imgui.h"
class ExampleLayer : public Neato::Layer
{
public:
	ExampleLayer()
		: Layer("Example"),
		m_Camera(-1.6f, 1.6f, -0.9f, 0.9f),
		m_CameraPosition(0.0f, 0.0f, 0.0f)
	{
		m_VertexArray.reset(Neato::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.1f, 0.4f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.6f, 0.2f, 1.0f,
			 0.0f,  0.5f, 0.0f,	0.7f, 0.2f, 0.5f, 1.0f
		};

		std::shared_ptr<Neato::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Neato::VertexBuffer::Create(vertices, sizeof(vertices)));

		Neato::BufferLayout layout = {
			{Neato::ShaderDataType::Float3, "a_Position"},
			{Neato::ShaderDataType::Float4, "a_Color"}
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = {
			0,1,2
		};

		std::shared_ptr<Neato::IndexBuffer> indexBuffer;
		indexBuffer.reset(Neato::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
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

		m_Shader.reset(new Neato::Shader(vertexSrc, fragSrc));
		m_Shader->Bind();

		m_SquareVA.reset(Neato::VertexArray::Create());

		float squareVert[3 * 4] = {
			 -0.75f, -0.75f, 0.0f,
			  0.75f, -0.75f, 0.0f,
			  0.75f,  0.75f, 0.0f,
			 -0.75f,  0.75f, 0.0f,
		};

		std::shared_ptr<Neato::VertexBuffer> squareVB;
		squareVB.reset(Neato::VertexBuffer::Create(squareVert, sizeof(squareVert)));

		Neato::BufferLayout layoutBlue = {
			{Neato::ShaderDataType::Float3, "a_Position"}
		};

		squareVB->SetLayout(layoutBlue);
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareInd[2 * 3] = {
			0,1,2,2,3,0
		};

		std::shared_ptr<Neato::IndexBuffer> squareIB;
		squareIB.reset(Neato::IndexBuffer::Create(squareInd, sizeof(squareInd) / sizeof(uint32_t)));
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

		m_BlueShader.reset(new Neato::Shader(blueVertexSrc, blueFragSrc));
		m_BlueShader->Bind();
	}

	void OnUpdate() override
	{
		if (Neato::Input::IsKeyPressed(NEATO_KEY_A))
			m_CameraPosition.x -= m_CameraSpeed;
		else if (Neato::Input::IsKeyPressed(NEATO_KEY_D))
			m_CameraPosition.x += m_CameraSpeed;

		if (Neato::Input::IsKeyPressed(NEATO_KEY_S))
			m_CameraPosition.y -= m_CameraSpeed;
		else if (Neato::Input::IsKeyPressed(NEATO_KEY_W))
			m_CameraPosition.y += m_CameraSpeed;

		if (Neato::Input::IsKeyPressed(NEATO_KEY_Q))
			m_CameraRotation += m_CameraRotationSpeed;
		else if (Neato::Input::IsKeyPressed(NEATO_KEY_E))
			m_CameraRotation -= m_CameraRotationSpeed;

		Neato::RenderCommand::SetClearColor({ 0.1f, 0.2f, 0.1f, 1 });
		Neato::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Neato::Renderer::BeginScene(m_Camera);
		Neato::Renderer::Submit(m_BlueShader, m_SquareVA);
		Neato::Renderer::Submit(m_Shader, m_VertexArray);
		Neato::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override {

	}

private:
	std::shared_ptr<Neato::Shader> m_Shader;
	std::shared_ptr<Neato::VertexArray> m_VertexArray;

	std::shared_ptr<Neato::Shader> m_BlueShader;
	std::shared_ptr<Neato::VertexArray> m_SquareVA;

	Neato::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 0.05f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 0.65f;
};


class Sandbox : public Neato::Application {
public:
    Sandbox() {
		PushLayer(new ExampleLayer());
    }

    ~Sandbox() {

    }
};

Neato::Application* Neato::CreateApplication()
{
    return new Sandbox();
}