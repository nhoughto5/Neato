#include <Neato.h>
#include <stdio.h>
#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>

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
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main() {
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ProjectionView * u_Transform * vec4(a_Position, 1.0);
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
			 -0.5f, -0.5f, 0.0f,
			  0.5f, -0.5f, 0.0f,
			  0.5f,  0.5f, 0.0f,
			 -0.5f,  0.5f, 0.0f,
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

		std::string flatColorVertrxSrc = R"(
			#version 330 core

			layout(location=0) in vec3 a_Position;
			uniform mat4 u_ProjectionView;
			uniform mat4 u_Transform;

			void main() {
				gl_Position = u_ProjectionView * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string flatColorFragSrc = R"(
			#version 330 core
			uniform vec4 u_Color;

			layout(location = 0) out vec4 color;
			void main() {
				//color = vec4(0.2, 0.3, 0.85, 1.0);
				color = u_Color;
			}
		)";

		m_flatColorShader.reset(new Neato::Shader(flatColorVertrxSrc, flatColorFragSrc));
		m_flatColorShader->Bind();
	}

	void OnUpdate(Neato::TimeStep ts) override
	{
		if (Neato::Input::IsKeyPressed(NEATO_KEY_A))
			m_CameraPosition.x -= m_CameraSpeed * ts;
		else if (Neato::Input::IsKeyPressed(NEATO_KEY_D))
			m_CameraPosition.x += m_CameraSpeed * ts;

		if (Neato::Input::IsKeyPressed(NEATO_KEY_S))
			m_CameraPosition.y -= m_CameraSpeed * ts;
		else if (Neato::Input::IsKeyPressed(NEATO_KEY_W))
			m_CameraPosition.y += m_CameraSpeed * ts;

		if (Neato::Input::IsKeyPressed(NEATO_KEY_Q))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		else if (Neato::Input::IsKeyPressed(NEATO_KEY_E))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		Neato::RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.30f, 1 });
		Neato::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Neato::Renderer::BeginScene(m_Camera);
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		glm::vec4 blueColor(0.2f, 0.3f, 0.85f, 1.0f);
		glm::vec4 redColor(0.8f, 0.2f, 0.35f, 1.0f);

		for (int j = 0; j < 20; ++j) {
			for (int i = 0; i < 20; ++i) {
				glm::vec3 pos(i * 0.11f, 0.11f * j, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				if (i % 2 == 0)
				{
					m_flatColorShader->UploadUniformFloat4("u_Color", redColor);
				}
				else
				{
					m_flatColorShader->UploadUniformFloat4("u_Color", blueColor);
				}
				Neato::Renderer::Submit(m_flatColorShader, m_SquareVA, transform);
			}
		}
		Neato::Renderer::Submit(m_Shader, m_VertexArray);
		Neato::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override {

	}

private:
	std::shared_ptr<Neato::Shader> m_Shader;
	std::shared_ptr<Neato::VertexArray> m_VertexArray;

	std::shared_ptr<Neato::Shader> m_flatColorShader;
	std::shared_ptr<Neato::VertexArray> m_SquareVA;

	Neato::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 7.0f;
	float m_SquareMoveSpeed = 1.0f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;
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