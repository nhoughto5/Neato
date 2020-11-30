#include <Neato.h>
#include <stdio.h>
#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Neato::Layer {
public:
    ExampleLayer()
        : Layer("Example"),
        m_CameraController(1280.0f / 720.0f) {
        m_VertexArray.reset(Neato::VertexArray::Create());

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.1f, 0.4f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.0f, 0.6f, 0.2f, 1.0f,
             0.0f,  0.5f, 0.0f,	0.7f, 0.2f, 0.5f, 1.0f
        };

        Neato::Ref<Neato::VertexBuffer> vertexBuffer;
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

        Neato::Ref<Neato::IndexBuffer> indexBuffer;
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

        m_Shader = Neato::Shader::Create("traingleShader", vertexSrc, fragSrc);
        m_Shader->Bind();

        m_SquareVA.reset(Neato::VertexArray::Create());

        float squareVert[5 * 4] = {
             -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
              0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
              0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
             -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
        };

        Neato::Ref<Neato::VertexBuffer> squareVB;
        squareVB.reset(Neato::VertexBuffer::Create(squareVert, sizeof(squareVert)));

        Neato::BufferLayout layoutBlue = {
            {Neato::ShaderDataType::Float3, "a_Position"},
            {Neato::ShaderDataType::Float2, "a_TexCoord"}
        };

        squareVB->SetLayout(layoutBlue);
        m_SquareVA->AddVertexBuffer(squareVB);

        uint32_t squareInd[2 * 3] = {
            0,1,2,2,3,0
        };

        Neato::Ref<Neato::IndexBuffer> squareIB;
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
			uniform vec3 u_Color;

			layout(location = 0) out vec4 color;
			void main() {
				color = vec4(u_Color, 1.0);
			}
		)";

        m_flatColorShader = Neato::Shader::Create("flatColorShader", flatColorVertrxSrc, flatColorFragSrc);
        m_flatColorShader->Bind();

        m_ShaderLib.Load("assets/shaders/Texture.glsl");

        m_Texture = Neato::Texture2D::Create("assets/textures/Checkerboard.png");
        m_TextureColours = Neato::Texture2D::Create("assets/textures/ChernoLogo.png");
        std::dynamic_pointer_cast<Neato::OpenGLShader>(m_ShaderLib.Get("Texture"))->Bind();
        std::dynamic_pointer_cast<Neato::OpenGLShader>(m_ShaderLib.Get("Texture"))->UploadUniformInt("u_Texture", 0);
    }

    void OnUpdate(Neato::TimeStep ts) override {
        m_CameraController.OnUpdate(ts);

        Neato::RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.30f, 1 });
        Neato::RenderCommand::Clear();

        Neato::Renderer::BeginScene(m_CameraController.GetCamera());
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        std::dynamic_pointer_cast<Neato::OpenGLShader>(m_flatColorShader)->Bind();
        std::dynamic_pointer_cast<Neato::OpenGLShader>(m_flatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

        for (int j = 0; j < 20; ++j) {
            for (int i = 0; i < 20; ++i) {
                glm::vec3 pos(i * 0.11f, 0.11f * j, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
                Neato::Renderer::Submit(m_flatColorShader, m_SquareVA, transform);
            }
        }

        m_Texture->Bind();
        Neato::Renderer::Submit(m_ShaderLib.Get("Texture"), m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        m_TextureColours->Bind();
        Neato::Renderer::Submit(m_ShaderLib.Get("Texture"), m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
        //Neato::Renderer::Submit(m_flatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
        //Neato::Renderer::Submit(m_Shader, m_VertexArray);
        Neato::Renderer::EndScene();
    }

    virtual void OnImGuiRender() override {
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
        ImGui::End();
    }

    void OnEvent(Neato::Event& e) override {
        m_CameraController.OnEvent(e);
    }

private:
    Neato::ShaderLibrary m_ShaderLib;
    Neato::Ref<Neato::Shader> m_Shader;
    Neato::Ref<Neato::VertexArray> m_VertexArray;

    Neato::Ref<Neato::Shader> m_flatColorShader;
    Neato::Ref<Neato::VertexArray> m_SquareVA;
    Neato::Ref<Neato::Texture2D> m_Texture, m_TextureColours;

    Neato::OrthographicCameraController m_CameraController;

    glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};


class Sandbox : public Neato::Application {
public:
    Sandbox() {
        PushLayer(new ExampleLayer());
    }

    ~Sandbox() {

    }
};

Neato::Application* Neato::CreateApplication() {
    return new Sandbox();
}