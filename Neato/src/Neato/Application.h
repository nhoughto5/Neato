#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "Neato/Events/ApplicationEvent.h"
#include "Neato/LayerStack.h"
#include "Window.h"
#include "ImGui/ImGuiLayer.h"
#include "Renderer/Buffer.h"
#include "Neato/Renderer/Shader.h"

namespace Neato {
    class NEATO_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		static Application* s_Instance;

		unsigned int m_VertexArray;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
    };

    // To be defined in client
    Application* CreateApplication();
}


